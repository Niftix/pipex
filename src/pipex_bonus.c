/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:26:56 by mville            #+#    #+#             */
/*   Updated: 2026/02/13 14:26:57 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	here_doc(char *limiter)
{
	int		fd;
	char	*line;
	int		size;

	size = ft_strlen(limiter);
	fd = open(".doc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (1);
	line = get_next_line(0);
	if (!line)
		return (1);
	while (line)
	{
		if (ft_strncmp(line, limiter, size) == 0)
			break ;
		else
			ft_putstr_fd(line, fd);
		free(line);
		line = get_next_line(0);
	}
	free(line);
	close(fd);
	return (0);
}

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

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int		status;

	if (ac < 5)
		return (1);
	if (ac >= 6 && ft_strncmp(av[1], "here_doc", 9) == 0)
		pipex.is_here_doc = 1;
	else
		pipex.is_here_doc = 0;
	if (pipex_init(&pipex, av, ac) == -1)
		return (1);
	if (pipex.is_here_doc == 1)
		here_doc(av[2]);
	if (parsing_core(envp, av, &pipex) == -1)
		return (1);
	status = pipex_core(&pipex, envp);
	ft_free_cmd(pipex.cmds_args, pipex.cmd_count);
	free_path(pipex.cmds_path, pipex.cmd_count);
	if (pipex.is_here_doc == 1)
		unlink(".doc_tmp");
	return (status);
}
