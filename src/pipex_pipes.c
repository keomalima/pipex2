/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 18:06:56 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/03 14:37:28 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	first_pipe(char **av, char **env, int pipe_fd[2])
{
	int		fd_in;
	char	**cmd;

	cmd = parse_arg(av[2], env);
	if (!cmd)
		exit_handler("Failed to get cmd path");
	fd_in = open(av[1], O_RDONLY);
	if (fd_in < 0)
		exit_handler(av[1]);
	if (dup2(fd_in, STDIN_FILENO) == -1 || dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		exit_handler("Failed to dup2");
	close_fds(pipe_fd);
	close(fd_in);
	if (execve(cmd[0], cmd, env) == -1)
	{
		free_split(cmd);
		exit_handler("Failed to execve");
	}
}

void	second_pipe(char **av, char **env, int pipe_fd[2])
{
	char	**cmd;
	int		fd_out;

	cmd = parse_arg(av[3], env);
	if (!cmd)
		exit_handler("Failed to get cmd path");
	fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
		exit_handler(av[4]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1 || dup2(fd_out, STDOUT_FILENO) == -1)
		exit_handler("Failed to dup2");
	close_fds(pipe_fd);
	close(fd_out);
	if (execve(cmd[0], cmd, env) == -1)
	{
		free_split(cmd);
		exit_handler("Failed to execve");
	}
}

void	pipex(char **av, char **env)
{
	int		pipe_fd[2];
	int		pid[2];
	int		i;

	if (pipe(pipe_fd) < 0)
		exit_handler("Failed to create pipe");
	i = 0;
	while (i < 2)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			exit_handler("Failed to fork");
		if (pid[i] == 0)
		{
			if (i == 0)
				first_pipe(av, env, pipe_fd);
			else
				second_pipe(av, env, pipe_fd);
		}
		i++;
	}
	close_fds(pipe_fd);
	while (i > 2)
	{
		if (waitpid(pid[i], NULL, 0) < 0)
			exit_handler("Failed to wait");
		i++;
	}
}
