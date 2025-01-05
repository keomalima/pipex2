/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 11:57:04 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/05 17:09:10 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include "../libft/includes/libft.h"

typedef struct s_args
{
	int		cmd_count;
	int		pipe_count;
	char	**av;
	char	**env;
	char	**cmd;
	int		**pipe_fd;
}				t_args;

void	pipex(t_args *args);
void	here_doc(t_args *args);
char	**parse_arg(t_args *args, char *arg);
void	exit_handler(t_args *args, int err_code);
void	free_split(char **arr);
void	wait_children(t_args *args);
char	*ft_join_path(const char *s1, const char *s2);
void	initialize_variables(int ac, char **av, char **env, t_args *args);
void	close_fds(t_args *args);
void	free_pipe_fds(t_args *args);
void	malloc_n_open_pipes(t_args *args);
void	open_pipes(t_args *args);
void	setup_pipes_fds(t_args *args, int fd[2], int i);

#endif
