/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:26:46 by mville            #+#    #+#             */
/*   Updated: 2026/02/13 14:26:47 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(char **res)
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

int	ft_free_cmd(t_cmd *cmd)
{
	free(cmd->cmd1_path);
	free(cmd->cmd2_path);
	ft_free(cmd->cmd1_tab);
	ft_free(cmd->cmd2_tab);
	return (-1);
}

void	init_cmd(t_cmd *cmd)
{
	cmd->cmd1_path = NULL;
	cmd->cmd2_path = NULL;
	cmd->cmd1_tab = NULL;
	cmd->cmd2_tab = NULL;
}

int	parent_exit(t_cmd *cmd, int *fd_pipe)
{
	ft_free_cmd(cmd);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	return (-1);
}

void	child_exit(t_cmd *cmd, int *fd_pipe, int code)
{
	ft_free_cmd(cmd);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	exit(code);
}
