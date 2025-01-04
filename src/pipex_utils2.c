/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 12:28:08 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/04 13:27:45 by keomalima        ###   ########.fr       */
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
		{
			while (i > 0)
			{
				close(args->pipe_fd[i - 1][0]);
				args->pipe_fd[i - 1][0] = -1;
				close(args->pipe_fd[i - 1][1]);
				args->pipe_fd[i - 1][1] = -1;
				i--;
			}
			exit_handler(args, "Failed to open pipes");
		}
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
	close_fds(args);
	i = 0;
	while (args->pipe_count > i)
		free(args->pipe_fd[i++]);
	free(args->pipe_fd);
	args->pipe_fd = NULL;
}

void	close_fds(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->pipe_count)
	{
		if (args->pipe_fd[i][0] >= 0)
		{
			close(args->pipe_fd[i][0]);
			args->pipe_fd[i][0] = -1;
		}
		if (args->pipe_fd[i][1] >= 0)
		{
			close(args->pipe_fd[i][1]);
			args->pipe_fd[i][1] = -1;
		}
		i++;
	}
}
