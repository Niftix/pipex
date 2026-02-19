/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:26:42 by mville            #+#    #+#             */
/*   Updated: 2026/02/13 14:26:43 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free(void **res)
{
	int	i;

	i = 0;
	if (!res)
		return ;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);
}

void	ft_free_cmd(char ***cmd, int count)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	while (i < count)
	{
		ft_free((void **)cmd[i]);
		i++;
	}
	free(cmd);
}

void	free_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	if (!pipes)
		return ;
	while (i < count)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	free_path(char **path, int count)
{
	int	i;

	i = 0;
	if (!path)
		return ;
	while (i < count)
	{
		free(path[i]);
		i++;
	}
	free(path);
}

void	child_free(t_pipex *pipex)
{
	ft_free_cmd(pipex->cmds_args, pipex->cmd_count);
	free_path(pipex->cmds_path, pipex->cmd_count);
	close_all(pipex->pipes, pipex->cmd_count - 1);
	free_pipes(pipex->pipes, pipex->cmd_count - 1);
	free(pipex->pid);
}
