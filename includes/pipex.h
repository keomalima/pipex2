/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 11:57:04 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/08 09:01:41 by kricci-d         ###   ########.fr       */
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
	char	**av;
	char	**env;
	char	**cmd;
}				t_args;

void	pipex(t_args *args);
char	**parse_arg(t_args *args, char *arg);
char	**ft_pipex_split(char const *s, char c);
void	open_pipes(t_args *args, int pipe_fd[2][2]);
void	close_fds(int pipe_fd[2][2]);
void	free_nsplit(char **tab, int index);
void	free_split(char **arr);
void	exit_handler(t_args *args, int err_code);

#endif
