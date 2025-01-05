/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 18:06:56 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/05 13:10:44 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	switch_io(t_args *args, int fd[2])
{
	int	dup_1;
	int dup_2;

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

void	pipex(t_args *args)
{
	int		i;
	int		fd[2];
	pid_t	pid;

	malloc_n_open_pipes(args);
	i = 0;
	while (args->cmd_count > i)
	{
		pid = fork();
		if (pid < 0)
			exit_handler(args, 1);
		if (pid == 0)
		{
			setup_pipes_fds(args, fd, i);
			args->cmd = parse_arg(args, args->av[i + 2]);
			switch_io(args, fd);
			close_fds(args);
			if (execve(args->cmd[0], args->cmd, args->env) == -1)
				exit_handler(args, 1);
		}
		i++;
	}
	close_fds(args);
	wait_children(args);
	free_pipe_fds(args);
}
