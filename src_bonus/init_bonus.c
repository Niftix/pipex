/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:27:11 by mville            #+#    #+#             */
/*   Updated: 2026/02/13 14:27:12 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	pipex_init(t_pipex *pipex, char **av, int ac)
{
	if (pipex->is_here_doc == 1)
	{
		pipex->cmd_count = ac - 4;
		pipex->infile = ".doc_tmp";
		pipex->outfile = av[ac - 1];
	}
	else
	{
		pipex->cmd_count = ac - 3;
		pipex->infile = av[1];
		pipex->outfile = av[ac - 1];
	}
	pipex->cmds_args = malloc(sizeof(char **) * pipex->cmd_count);
	if (!pipex->cmds_args)
		return (-1);
	pipex->cmds_path = malloc(sizeof(char *) * pipex->cmd_count);
	if (!pipex->cmds_path)
	{
		free(pipex->cmds_args);
		return (-1);
	}
	return (0);
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
			free_pipes(pipes, i);
			return (NULL);
		}
		pipe(pipes[i]);
		i++;
	}
	return (pipes);
}

void	infile_init(int i, t_pipex *pipex)
{
	int	fd;

	if (i == 0)
	{
		fd = open(pipex->infile, O_RDONLY);
		if (fd == -1)
		{
			perror(pipex->infile);
			child_free(pipex);
			exit(1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else
	{
		dup2(pipex->pipes[i - 1][0], STDIN_FILENO);
		close(pipex->pipes[i - 1][0]);
	}
}

void	output_init(int i, t_pipex *pipex)
{
	int	fd;

	if (i == pipex->cmd_count - 1)
	{
		if (pipex->is_here_doc == 1)
			fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror(pipex->outfile);
			child_free(pipex);
			exit(1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else
	{
		dup2(pipex->pipes[i][1], STDOUT_FILENO);
		close(pipex->pipes[i][1]);
	}
}
