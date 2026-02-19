/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:26:20 by mville            #+#    #+#             */
/*   Updated: 2026/02/13 14:26:21 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*find_access(char **res, char *cmd_name)
{
	int		i;
	char	*path;
	char	*tmp;

	i = 0;
	if (!cmd_name || !cmd_name[0])
		return (NULL);
	if (access(cmd_name, X_OK) == 0)
		return (ft_strdup(cmd_name));
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

static int	parse_path(char **envp, int path_index, t_pipex *pipex)
{
	char	**res;
	int		i;

	i = 0;
	res = ft_split(envp[path_index] + 5, ':');
	if (!res)
	{
		ft_free_cmd(pipex->cmds_args, pipex->cmd_count);
		free(pipex->cmds_path);
		return (-1);
	}
	while (i < pipex->cmd_count)
	{
		pipex->cmds_path[i] = find_access(res, pipex->cmds_args[i][0]);
		i++;
	}
	ft_free((void **)res);
	return (0);
}

static int	parse_cmd(t_pipex *pipex, char **av)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count)
	{
		pipex->cmds_args[i] = ft_split(av[2 + i + pipex->is_here_doc], ' ');
		if (!pipex->cmds_args[i])
		{
			ft_free_cmd(pipex->cmds_args, i);
			return (-1);
		}
		i++;
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

int	parsing_core(char **envp, char **av, t_pipex *pipex)
{
	int	path_index;

	path_index = find_path(envp);
	if (path_index == -1)
		return (-1);
	if (parse_cmd(pipex, av) == -1)
		return (-1);
	if (parse_path(envp, path_index, pipex) == -1)
		return (-1);
	return (0);
}
