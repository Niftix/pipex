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

static void	close_all(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	child_free(t_pipex *pipex)
{
	ft_free_cmd(pipex->cmds_args, pipex->cmd_count);
	free_path(pipex->cmds_path, pipex->cmd_count);
	close_all(pipex->pipes, pipex->cmd_count - 1);
	free_pipes(pipex->pipes, pipex->cmd_count - 1);
	free(pipex->pid);
}

void	pipex_exec(int i, t_pipex *pipex, char **envp)
{
	infile_init(i, pipex);
	output_init(i, pipex);
	close_all(pipex->pipes, pipex->cmd_count - 1);
	if (!pipex->cmds_path[i])
	{
		ft_putstr_fd(pipex->cmds_args[i][0], 2);
		if (access(pipex->cmds_args[i][0], F_OK) == 0)
		{
			ft_putstr_fd(": Permission denied\n", 2);
			child_free(pipex);
			exit(126);
		}
		ft_putstr_fd(": command not found\n", 2);
		child_free(pipex);
		exit(127);
	}
	execve(pipex->cmds_path[i], pipex->cmds_args[i], envp);
	child_free(pipex);
	exit(127);
}

static int	wait_children(int cmd_count, int *pid)
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
	int	status;
	int	i;

	pipex->pid = malloc(sizeof(int) * pipex->cmd_count);
	if (!pipex->pid)
		return (-1);
	pipex->pipes = create_pipes(pipex->cmd_count - 1);
	if (!pipex->pipes)
	{
		free(pipex->pid);
		return (-1);
	}
	i = 0;
	while (i < pipex->cmd_count)
	{
		pipex->pid[i] = fork();
		if (pipex->pid[i] == 0)
			pipex_exec(i, pipex, envp);
		i++;
	}
	close_all(pipex->pipes, pipex->cmd_count - 1);
	free_pipes(pipex->pipes, pipex->cmd_count - 1);
	status = wait_children(pipex->cmd_count, pipex->pid);
	free(pipex->pid);
	return (status);
}
