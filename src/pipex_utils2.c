/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 12:28:08 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/04 12:58:08 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_pipes(t_args *args)
{
	int	i;

	i = 0;
	while (args->pipe_count > i)
	{
		if (pipe(args->pipe_fd[i]) == -1)
			exit_handler(args, "Failed to open pipes");
		i++;
	}
}

void	malloc_n_open_pipes(t_args *args)
{
	int	i;

	args->pipe_fd = malloc(sizeof(int *) * (args->pipe_count));
	if (!args->pipe_fd)
		exit_handler(args, "Failed to malloc pipes");
	i = 0;
	while (args->pipe_count > i)
	{
		args->pipe_fd[i] = malloc (sizeof(int) * 2);
		if (!args->pipe_fd[i])
		{
			while (i > 0)
			{
				free(args->pipe_fd[i - 1]);
				i--;
			}
			free(args->pipe_fd);
			exit_handler(args, "Failed to malloc pipes");
		}
		i++;
	}
	open_pipes(args);
}

void	free_pipe_fds(t_args *args)
{
	int	i;

	if (!args->pipe_fd)
		return ;
	i = 0;
	while (args->pipe_count > i)
		free(args->pipe_fd[i++]);
	free(args->pipe_fd);
}

void	close_fds(t_args *args, int fd_in, int fd_out, int index)
{
	int	i;

	i = 0;
	if (index == 0 && fd_in > 0)
		close(fd_in);
	if (index == args->pipe_count && fd_out > 0)
		close(fd_out);
	while (args->pipe_count > i)
	{
		if (args->pipe_fd[i][0] > 0)
			close(args->pipe_fd[i][0]);
		if (args->pipe_fd[i][1] > 0)
			close(args->pipe_fd[i][1]);
		i++;
	}
}
