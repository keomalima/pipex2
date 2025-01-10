/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 18:06:56 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/10 14:55:58 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	wait_children(t_args *args)
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

void	close_fd(t_args *args, int *fd)
{
	if (close(*fd) < 0)
		exit_handler(args, 1);
	*fd = -1;
}

void	print_active_fds(t_args *args)
{
	if (args->pipe_fd[0][0] > 0)
		printf("pipe[0][0] is active\n");
	else
		printf("pipe[0][0] is inactive\n");
	if (args->pipe_fd[0][1] > 0)
		printf("pipe[0][1] is active\n");
	else
		printf("pipe[0][1] is inactive\n");
	if (args->pipe_fd[1][0] > 0)
		printf("pipe[1][0] is active\n");
	else
		printf("pipe[1][0] is inactive\n");
	if (args->pipe_fd[1][1] > 0)
		printf("pipe[1][1] is active\n");
	else
		printf("pipe[1][1] is inactive\n");
}

void	set_fd_out(t_args *args, int i)
{
	close_fd(args, &args->pipe_fd[i % 2][1]);
	args->pipe_fd[i % 2][1] = open(args->av[args->ac - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (args->pipe_fd[i % 2][1] < 0)
		ft_printf("permission denied: %s\n",
		args->av[args->cmd_count + 2]);
	if (args->pipe_fd[i % 2][1] < 0)
		exit_handler(args, -1);
}

void	set_fd_in(t_args *args, int i)
{
	close_fd(args, &args->pipe_fd[0][0]);
	args->pipe_fd[(i + 1) % 2][0] = open(args->av[1], O_RDONLY);
	if (args->pipe_fd[(i + 1) % 2][0] < 0)
	{
		if (access(args->av[1], R_OK ) < 0
				&& access(args->av[1], F_OK ) == 0)
			ft_printf("permission denied: %s \n", args->av[1]);
		else
			ft_printf("no such file or directory: %s\n", args->av[1]);
	}
	if (args->pipe_fd[(i + 1) % 2][0] < 0)
		exit_handler(args, -1);
}

void	switch_io_n_execve(t_args *args, int i)
{
	/* printf("-------\nIteration n %i\n", i);
	print_active_fds(args); */
	if (i == 0)
		set_fd_in(args, i);
	if (i == args->cmd_count - 1)
	{
		close_fd(args, &args->pipe_fd[i % 2][0]);
		set_fd_out(args, i);
	}
	args->cmd = parse_arg(args, args->av[i + 2 + args->here_doc]);
	if (dup2(args->pipe_fd[(i + 1) % 2][0], STDIN_FILENO) < 0)
		exit_handler(args, 1);
	if (dup2(args->pipe_fd[i % 2][1], STDOUT_FILENO) < 0)
		exit_handler(args, 1);
	close_fd(args, &args->pipe_fd[(i + 1) % 2][0]);
	close_fd(args, &args->pipe_fd[i % 2][1]);
	/* printf("Iteration n %i\n", i);
	print_active_fds(args); */
	if (execve(args->cmd[0], args->cmd, args->env) == -1)
		exit_handler(args, 1);
}

void	pipex(t_args *args)
{
	int	i;

	args->child_pids = malloc (args->cmd_count * sizeof(pid_t));
	if (!args->child_pids)
		exit_handler(args, 1);
	i = -1;
	while (args->cmd_count > ++i)
	{
		if (pipe(args->pipe_fd[i % 2]) < 0)
			exit_handler(args, 1);
		args->child_pids[i] = fork();
		if (args->child_pids[i] < 0)
			exit_handler(args, -1);
		if (args->child_pids[i] == 0)
			switch_io_n_execve(args, i);
		close_fd(args, &args->pipe_fd[i % 2][1]);
		if (i != 0)
			close_fd(args, &args->pipe_fd[(i + 1) % 2][0]);
		if (i == args->cmd_count - 1)
			close_fd(args, &args->pipe_fd[i % 2][0]);
	}
	wait_children(args);
}
