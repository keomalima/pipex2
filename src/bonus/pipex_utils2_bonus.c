/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 12:28:08 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/05 17:03:35 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	setup_pipes_fds(t_args *args, int fd[2], int i)
{
	if (i == 0)
		fd[0] = open(args->av[1], O_RDONLY);
	else
		fd[0] = args->pipe_fd[i - 1][0];
	if (i == args->pipe_count)
		fd[1] = open(args->av[args->cmd_count + 2],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd[1] = args->pipe_fd[i][1];
	if (fd[0] < 0 || fd[1] < 0)
	{
		if (fd[0] < 0)
			ft_printf("no such file or directory: %s\n", args->av[1]);
		if (fd[1] < 0)
			ft_printf("permission denied: %s\n",
				args->av[args->cmd_count + 2]);
		exit_handler(args, 0);
	}
}

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
			exit_handler(args, 1);
		}
		i++;
	}
}

void	malloc_n_open_pipes(t_args *args)
{
	int	i;

	args->pipe_fd = malloc(sizeof(int *) * (args->pipe_count));
	if (!args->pipe_fd)
		exit_handler(args, 12);
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
			args->pipe_fd = NULL;
			exit_handler(args, 12);
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
