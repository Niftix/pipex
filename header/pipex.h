/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:24:34 by mville            #+#    #+#             */
/*   Updated: 2026/02/13 14:24:37 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>

typedef struct s_cmd
{
	char	*cmd1_path;
	char	*cmd2_path;
	char	**cmd1_tab;
	char	**cmd2_tab;
}	t_cmd;

typedef struct s_pipe
{
	int	fd_pipe[2];
	int	pid1;
	int	pid2;
	int	status;
}	t_pipe;

/* LIBFT */
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
void	ft_putstr_fd(char *str, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
/* PIPEX */
int		pipex_core(char **av, t_cmd *cmd, char **envp);
/* UTILS */
int		ft_free_cmd(t_cmd *cmd);
int		parent_exit(t_cmd *cmd, int *fd_pipe);
void	child_exit(t_cmd *cmd, int *fd_pipe, int code);
void	ft_free(char **res);
void	init_cmd(t_cmd *cmd);
/* PARSING */
int		parsing_core(char **envp, char **av, t_cmd *cmd);

#endif
