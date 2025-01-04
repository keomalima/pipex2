/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 18:06:56 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/04 12:58:49 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	create_dup_env(t_args *args, int i)
{
	int	fd_in;
	int	fd_out;

	if (i == 0)
		fd_in = open(args->av[1], O_RDONLY);
	else
		fd_in = args->pipe_fd[i - 1][0];
	if (i == args->pipe_count)
		fd_out = open(args->av[args->cmd_count + 2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd_out = args->pipe_fd[i][1];
	if (fd_in < 0 || fd_out < 0)
		exit_handler(args, "Failed to open file descriptor");
	if (dup2(fd_in, STDIN_FILENO) == -1 || dup2(fd_out, STDOUT_FILENO) == -1)
	{
		close_fds(args, fd_in, fd_out, i);
		exit_handler(args, "Failed to dup2");
	}
	close_fds(args, fd_in, fd_out, i);
}

void	child_handler(t_args *args, int i)
{
	int		pid;

	pid = fork();
	if (pid < 0)
		exit_handler(args, "");
	if (pid == 0)
	{
		args->cmd = parse_arg(args, args->av[i + 2]);
		create_dup_env(args, i);
		if (execve(args->cmd[0], args->cmd, args->env) == -1)
			exit_handler(args, "");
	}
}

void	pipex(t_args *args)
{
	int	i;

	malloc_n_open_pipes(args);
	i = 0;
	while (args->cmd_count > i)
		child_handler(args, i++);
	close_fds(args, 0, 0, i);
	i = 0;
	while (args->cmd_count > i)
	{
		if (wait(NULL) < 0)
			exit_handler(args, "Failed to wait");
		i++;
	}
	free_pipe_fds(args);
}
