/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:24:46 by mville            #+#    #+#             */
/*   Updated: 2026/02/13 14:24:48 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	char	*infile;
	char	*outfile;
	char	***cmds_args;
	char	**cmds_path;
	int		cmd_count;
	int		is_here_doc;
}	t_pipex;

/* LIBFT */
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);

/* GNL */
char	*get_next_line(int fd);

/* Init */
int		pipex_init(t_pipex *pipex, char **av, int ac);
void	infile_init(int i, int **pipes, t_pipex *pipex);
void	output_init(int i, int **pipes, t_pipex *pipex);

/* Parsing */
int		parsing_core(char **envp, char **av, t_pipex *pipex);

/* Exec */
int		pipex_core(t_pipex *pipex, char **envp);
int		**create_pipes(int size);
int		wait_children(int cmd_count, int *pid);
void	close_all(int **pipes, int count);

/* Utils */
void	ft_free(void **res);
void	ft_free_cmd(char ***cmd, int count);
void	free_pipes(int **pipes, int count);
void	free_path(char **path, int count);

#endif
