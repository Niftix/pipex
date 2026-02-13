/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:26:25 by mville            #+#    #+#             */
/*   Updated: 2026/02/13 14:26:26 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*find_access(char **res, char *cmd_name)
{
	int		i;
	char	*path;
	char	*tmp;

	i = 0;
	if (!cmd_name || !cmd_name[0])
		return (NULL);
	if (access(cmd_name, X_OK) == 0)
		return (cmd_name);
	while (res[i])
	{
		path = ft_strjoin(res[i], "/");
		if (!path)
			return (NULL);
		tmp = path;
		path = ft_strjoin(path, cmd_name);
		free(tmp);
		if (!path)
			return (NULL);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

static int	parse_path(char **envp, int path_index, t_cmd *cmd)
{
	char	**res;

	res = ft_split(envp[path_index] + 5, ':');
	if (!res)
		return (-1);
	cmd->cmd1_path = find_access(res, cmd->cmd1_tab[0]);
	cmd->cmd2_path = find_access(res, cmd->cmd2_tab[0]);
	if (!cmd->cmd1_path && !cmd->cmd2_path)
	{
		ft_free(res);
		ft_free_cmd(cmd);
		return (-1);
	}
	ft_free(res);
	return (0);
}

static int	parse_cmd(t_cmd *cmd, char **av)
{
	cmd->cmd1_tab = ft_split(av[2], ' ');
	if (!cmd->cmd1_tab)
		return (-1);
	cmd->cmd2_tab = ft_split(av[3], ' ');
	if (!cmd->cmd2_tab)
	{
		ft_free_cmd(cmd);
		return (-1);
	}
	return (0);
}

static int	find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (i);
		else
			i++;
	}
	return (-1);
}

int	parsing_core(char **envp, char **av, t_cmd *cmd)
{
	int	path_index;

	path_index = find_path(envp);
	if (path_index == -1)
		return (-1);
	if (parse_cmd(cmd, av) == -1)
		return (-1);
	if (parse_path(envp, path_index, cmd) == -1)
		return (-1);
	return (0);
}
