/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 18:06:56 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/13 10:15:52 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	wait_children_exit(t_args *args)
{
	int	i;
	int	status;

	i = 0;
	while (args->cmd_count > i)
	{
		if (waitpid(args->child_pids[i], &status, 0) < 0)
			exit_handler(args, 1);
		i++;
	}
	free(args->child_pids);
	exit(WEXITSTATUS(status));
}

void	open_file(t_args *args, int i)
{
	if (i == 0)
	{
		args->pipe_fd[(i + 1) % 2][0] = open(args->av[1], O_RDONLY);
		if (args->pipe_fd[(i + 1) % 2][0] < 0)
		{
			if (access(args->av[1], R_OK) < 0
				&& access(args->av[1], F_OK) == 0)
				ft_printf("%s: %s \n", strerror(errno), args->av[1]);
			else
				ft_printf("%s: %s \n", strerror(errno), args->av[1]);
			exit_handler(args, -1);
		}
	}
	else
	{
		args->pipe_fd[i % 2][1] = open(args->av[args->ac - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (args->pipe_fd[i % 2][1] < 0)
		{
			ft_printf("%s: %s \n", strerror(errno),
				args->av[args->cmd_count + 2]);
			exit_handler(args, -1);
		}
	}
}

void	switch_io_n_execve(t_args *args, int i)
{
	if (i == 0 || i == args->cmd_count - 1)
		open_file(args, i);
	args->cmd = parse_arg(args, args->av[i + 2]);
	if (dup2(args->pipe_fd[(i + 1) % 2][0], STDIN_FILENO) < 0)
		exit_handler(args, 1);
	if (dup2(args->pipe_fd[i % 2][1], STDOUT_FILENO) < 0)
		exit_handler(args, 1);
	close_all_fds(args);
	if (execve(args->cmd[0], args->cmd, args->env) == -1)
		exit_handler(args, 1);
}

void	pipex(t_args *args)
{
	int	i;

	args->child_pids = malloc (args->cmd_count * sizeof(pid_t));
	if (!args->child_pids)
		exit_handler(args, 1);
	i = 0;
	while (args->cmd_count > i)
	{
		if (args->cmd_count - 1 > i)
			if (pipe(args->pipe_fd[i % 2]) < 0)
				exit_handler(args, 1);
		args->child_pids[i] = fork();
		if (args->child_pids[i] < 0)
			exit_handler(args, -1);
		if (args->child_pids[i] == 0)
			switch_io_n_execve(args, i);
		close_fd(args, &args->pipe_fd[i % 2][1]);
		close_fd(args, &args->pipe_fd[(i + 1) % 2][0]);
		i++;
	}
	wait_children_exit(args);
}
