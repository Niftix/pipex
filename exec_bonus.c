/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:26:32 by mville            #+#    #+#             */
/*   Updated: 2026/02/13 14:26:33 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	pipex_exec(int i, t_pipex *pipex, int **pipes, char **envp)
{
	infile_init(i, pipes, pipex);
	output_init(i, pipes, pipex);
	close_all(pipes, pipex->cmd_count - 1);
	execve(pipex->cmds_path[i], pipex->cmds_args[i], envp);
	exit(127);
}

int	wait_children(int cmd_count, int *pid)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < cmd_count)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	return (WEXITSTATUS(status));
}

int	pipex_core(t_pipex *pipex, char **envp)
{
	int	**pipes;
	int	*pid;
	int	status;
	int	i;

	pid = malloc(sizeof(int) * pipex->cmd_count);
	if (!pid)
		return (-1);
	i = 0;
	pipes = create_pipes(pipex->cmd_count - 1);
	if (!pipes)
		return (-1);
	while (i < pipex->cmd_count)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			pipex_exec(i, pipex, pipes, envp);
		i++;
	}
	close_all(pipes, pipex->cmd_count - 1);
	free_pipes(pipes, pipex->cmd_count - 1);
	status = wait_children(pipex->cmd_count, pid);
	free(pid);
	return (status);
}

int	**create_pipes(int size)
{
	int	**pipes;
	int	i;

	i = 0;
	pipes = malloc(sizeof(int *) * size);
	if (!pipes)
		return (NULL);
	while (i < size)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			ft_free((void **)pipes);
			return (NULL);
		}
		pipe(pipes[i]);
		i++;
	}
	return (pipes);
}
