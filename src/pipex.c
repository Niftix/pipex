/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:26:14 by mville            #+#    #+#             */
/*   Updated: 2026/02/13 14:26:15 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_two(char **av, t_cmd *cmd, int *fd_pipe, char **envp)
{
	int	fd;

	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(av[4]);
		child_exit(cmd, fd_pipe, 1);
	}
	if (dup2(fd_pipe[0], 0) == -1)
		child_exit(cmd, fd_pipe, 1);
	if (dup2(fd, 1) == -1)
		child_exit(cmd, fd_pipe, 1);
	close(fd);
	if (!cmd->cmd2_path)
	{
		ft_putstr_fd(cmd->cmd2_tab[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		child_exit(cmd, fd_pipe, 127);
	}
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	if (execve(cmd->cmd2_path, cmd->cmd2_tab, envp) == -1)
		ft_free_cmd(cmd);
	exit(1);
}

static void	child_one(char **av, t_cmd *cmd, int *fd_pipe, char **envp)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		perror(av[1]);
		child_exit(cmd, fd_pipe, 1);
	}
	if (dup2(fd, 0) == -1)
		child_exit(cmd, fd_pipe, 1);
	close(fd);
	if (dup2(fd_pipe[1], 1) == -1)
		child_exit(cmd, fd_pipe, 1);
	if (!cmd->cmd1_path)
	{
		ft_putstr_fd(cmd->cmd1_tab[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		child_exit(cmd, fd_pipe, 127);
	}
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	if (execve(cmd->cmd1_path, cmd->cmd1_tab, envp) == -1)
		ft_free_cmd(cmd);
	exit(1);
}

int	pipex_core(char **av, t_cmd *cmd, char **envp)
{
	t_pipe	pipex;

	if (pipe(pipex.fd_pipe) == -1)
		return (ft_free_cmd(cmd));
	pipex.pid1 = fork();
	if (pipex.pid1 == -1)
		return (parent_exit(cmd, pipex.fd_pipe));
	else if (pipex.pid1 == 0)
		child_one(av, cmd, pipex.fd_pipe, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == -1)
		return (parent_exit(cmd, pipex.fd_pipe));
	else if (pipex.pid2 == 0)
		child_two(av, cmd, pipex.fd_pipe, envp);
	close(pipex.fd_pipe[0]);
	close(pipex.fd_pipe[1]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, &pipex.status, 0);
	ft_free_cmd(cmd);
	if (WIFEXITED(pipex.status))
		return (WEXITSTATUS(pipex.status));
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	cmd;
	int		return_nb;

	if (ac != 5)
		return (1);
	init_cmd(&cmd);
	if (parsing_core(envp, av, &cmd) == -1)
		return (1);
	return_nb = pipex_core(av, &cmd, envp);
	if (return_nb == -1)
		return (1);
	return (return_nb);
}
