/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 18:06:56 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/03 15:51:38 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	create_dup_env(char **av, int i, int pipe_fd[2])
{
	int		fd_in;
	int		fd_out;

	if (i == 0)
	{
		fd_in = open(av[1], O_RDONLY);
		if (fd_in < 0)
			return (1);
		fd_out = pipe_fd[1];
	}
	else
	{
		fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0)
			return (1);
		fd_in = pipe_fd[0];
	}
	if (dup2(fd_in, STDIN_FILENO) == -1 || dup2(fd_out, STDOUT_FILENO) == -1)
		return (1);
	close_fds(pipe_fd);
	return (0);
}

void	fork_env(char **av, char**env, char **cmd, int pipe_fd[2], int i)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		free_split(cmd);
		exit_handler("");
	}
	if (pid == 0)
	{
		if (create_dup_env(av, i, pipe_fd) == 1)
		{
			free_split(cmd);
			exit_handler("");
		}
		if (execve(cmd[0], cmd, env) == -1)
		{
			free_split(cmd);
			exit_handler("");
		}
	}
}

void	pipex(char **av, int ac, char **env)
{
	int		pipe_fd[2];
	int		i;
	char	**cmd;

	if (pipe(pipe_fd) < 0)
		exit_handler("Failed to create pipe");
	i = 0;
	while (ac - 3 > i)
	{
		cmd = parse_arg(av[i + 2], env);
		if (!cmd)
			exit_handler("Failed to parse_arg");
		fork_env(av, env, cmd, pipe_fd, i);
		free_split(cmd);
		i++;
	}
	close_fds(pipe_fd);
	i = 0;
	while (ac - 3 > i)
	{
		if (wait(NULL) < 0)
			exit_handler("Failed to wait");
		i++;
	}
}
