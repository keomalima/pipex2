/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 11:57:04 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/05 12:23:40 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
void	initialize_variables(int ac, char **av, char **env, t_args *args);
char	**parse_arg(t_args *args, char *arg);
char	*ft_join_path(const char *s1, const char *s2);
void	malloc_n_open_pipes(t_args *args);
void	setup_pipes_fds(t_args *args, int fd[2], int i);
void	wait_children(t_args *args);
void	free_split(char **arr);
void	free_pipe_fds(t_args *args);
void	close_fds(t_args *args);
void	exit_handler(t_args *args, int err_code);


#endif
