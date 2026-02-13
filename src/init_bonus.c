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

void	infile_init(int i, int **pipes, t_pipex *pipex)
{
	int	fd;

	if (i == 0)
	{
		fd = open(pipex->infile, O_RDONLY);
		if (fd == -1)
		{
			perror(pipex->infile);
			exit(1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
		close(pipes[i - 1][0]);
	}
}

void	output_init(int i, int **pipes, t_pipex *pipex)
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
			exit(1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else
	{
		dup2(pipes[i][1], STDOUT_FILENO);
		close(pipes[i][1]);
	}
}
