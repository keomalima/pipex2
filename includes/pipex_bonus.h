/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 11:57:04 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/11 15:35:17 by keomalima        ###   ########.fr       */
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
	int		here_doc;
	int		ac;
	char	**av;
	char	**env;
	char	**cmd;
	int		pipe_fd[2][2];
	pid_t	*child_pids;
}				t_args;

void	pipex(t_args *args);
char	**ft_pipex_split(char const *s, char c);
int		pipex_here_doc(t_args *args);
char	**parse_arg(t_args *args, char *arg);
void	close_all_fds(t_args *args);
void	close_fd(t_args *args, int *fd);
void	free_split(char **arr);
void	free_nsplit(char **tab, int index);
void	exit_handler(t_args *args, int err_code);

#endif
