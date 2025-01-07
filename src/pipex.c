/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 18:06:56 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/07 11:01:33 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	wait_children(t_args *args)
{
	int	i;
	int	status;
	int	exit_status;
	int	child_exit_status;

	i = 0;
	exit_status = 0;
	while (args->cmd_count > i)
	{
		if (waitpid(-1, &status, 0) < 0)
			exit_handler(args, 1);
		if (WIFEXITED(status))
		{
			child_exit_status = WEXITSTATUS(status);
			if (child_exit_status != 0)
				exit_status = child_exit_status;
		}
		i++;
	}
	exit(exit_status);
}

void	switch_io(t_args *args, int fd[2])
{
	int	dup_1;
	int	dup_2;

	dup_1 = dup2(fd[0], STDIN_FILENO);
	dup_2 = dup2(fd[1], STDOUT_FILENO);
	if (dup_1 == -1 || dup_2 == -1)
	{
		close(fd[0]);
		close(fd[1]);
		exit_handler(args, 1);
	}
	close(fd[0]);
	close(fd[1]);
}

void	setup_pipes_fds(t_args *args, int fd[2], int i, int pipe_fd[2][2])
{
	if (i == 0)
		fd[0] = open(args->av[1], O_RDONLY);
	else
		fd[0] = pipe_fd[i % 2 == 0][0];
	if (i == args->cmd_count - 1)
		fd[1] = open(args->av[args->cmd_count + 2],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd[1] = pipe_fd[i % 2][1];
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

void	pipex(t_args *args)
{
	int	i;
	int	dup_fd[2];
	int	pipe_fd[2][2];
	int	pid;

	open_pipes(args, pipe_fd);
	i = 0;
	while (args->cmd_count > i)
	{
		pid = fork();
		if (pid < 0)
			exit_handler(args, 1);
		if (pid == 0)
		{
			setup_pipes_fds(args, dup_fd, i, pipe_fd);
			args->cmd = parse_arg(args, args->av[i + 2]);
			switch_io(args, dup_fd);
			close_fds(pipe_fd);
			if (execve(args->cmd[0], args->cmd, args->env) == -1)
				exit_handler(args, 1);
		}
		i++;
	}
	close_fds(pipe_fd);
	wait_children(args);
}
