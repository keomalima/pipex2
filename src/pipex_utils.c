/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 18:01:41 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/06 12:22:33 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	initialize_variables(int ac, char **av, char **env, t_args *args)
{
	args->cmd_count = ac - 3;
	args->pipe_count = ac - 4;
	args->av = av;
	args->env = env;
	args->cmd = NULL;
}

void	open_pipes(t_args *args, int pipe_fd[2][2])
{
	if (pipe(pipe_fd[0]) == -1)
		exit_handler(args, 1);
	if (pipe(pipe_fd[1]) == -1)
		exit_handler(args, 1);
}

void	close_fds(int fd[2][2])
{
	if (fd[0][0] >= 0)
		close(fd[0][0]);
	if (fd[0][1] >= 0)
		close(fd[0][1]);
	if (fd[1][0] >= 0)
		close(fd[1][0]);
	if (fd[1][1] >= 0)
		close(fd[1][1]);
}

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	arr = NULL;
}

void	exit_handler(t_args *args, int err_code)
{
	if (args->cmd)
		free_split(args->cmd);
	if (err_code == 0)
		errno = 0;
	if (err_code == 12)
		errno = ENOMEM;
	if (errno)
		perror("Error");
	exit(EXIT_FAILURE);
}
