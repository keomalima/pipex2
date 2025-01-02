/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 18:06:56 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/02 20:54:20 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	first_pipe(t_filed *fd, char **cmd, int pipe_fd[2])
{
	int	fd_in;

	fd_in = open(fd->av[1], O_RDONLY);
	if (fd_in < 0)
	{
		print_err_msg(fd->av[1]);
		return (1);
	}
	close(pipe_fd[0]);
	dup2(fd_in, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	close(fd_in);
	execve(cmd[0], cmd, fd->env);
	return (0);
}

int	second_pipe(t_filed *fd, char **cmd, int pipe_fd[2])
{
	int	fd_out;

	fd_out = open(fd->av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
	{
		print_err_msg(fd->av[4]);
		return (1);
	}
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(pipe_fd[0]);
	close(fd_out);
	execve(cmd[0], cmd, fd->env);
	return (0);
}

int	run(t_filed *fd, int pipe_fd[2], char **path_env)
{
	int		pid[2];
	int		i;
	char	**cmd;

	i = 0;
	while (i < 2)
	{
		cmd = parse_arg(fd->av[i + 2], path_env);
		pid[i] = fork();
		if (pid[i] == 0)
		{
			if (i == 0)
				first_pipe(fd, cmd, pipe_fd);
			else
				second_pipe(fd, cmd, pipe_fd);
		}
		free_split(cmd);
		i++;
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	wait(NULL);
	wait(NULL);
	return (0);
}

int	pipex_run_pipes(t_filed *fd)
{
	char	**path_env;
	int		pipe_fd[2];

	path_env = parse_path_env(fd);
	pipe(pipe_fd);
	if (!path_env)
		return (1);
	if (run(fd, pipe_fd, path_env) == 1)
	{
		free_split(path_env);
		print_err_msg("");
		return (1);
	}
	free_split(path_env);
	return (0);
}
