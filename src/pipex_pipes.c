/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 18:06:56 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/03 16:54:52 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	create_dup_env(char **av, int ac, int i, int **pipe_fd)
{
	int	fd_in;
	int	fd_out;

	if (i == 0)
	{
		fd_in = open(av[1], O_RDONLY);
		if (fd_in < 0)
			return (1);
		fd_out = pipe_fd[i][1];
	}
	else if (i == ac - 4)
	{
		fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0)
			return (1);
		fd_in = pipe_fd[i - 1][0];
	}
	else
	{
		fd_in = pipe_fd[i - 1][0];
		fd_out = pipe_fd[i][1];
	}
	if (dup2(fd_in, STDIN_FILENO) == -1 || dup2(fd_out, STDOUT_FILENO) == -1)
		return (1);
	close_fds(ac, pipe_fd);
	return (0);
}

void	child_handler(char **av, int ac, char**env, int **pipe_fd, int i)
{
	int		pid;
	char	**cmd;

	pid = fork();
	if (pid < 0)
		exit_handler("");
	if (pid == 0)
	{
		cmd = parse_arg(av[i + 2], env);
		if (!cmd)
			exit_handler("Failed to parse_arg");
		if (create_dup_env(av, ac, i, pipe_fd) == 1)
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

int	open_pipes(int ac, int ***pipe_fd)
{
	int	i;

	*pipe_fd = malloc(sizeof(int *) * (ac - 4));
	if (!*pipe_fd)
		return (1);
	i = 0;
	while (ac - 4 > i)
	{
		(*pipe_fd)[i] = malloc (sizeof(int) * 2);
		if (!(*pipe_fd)[i])
		{
			while (i > 0)
			{
				free(pipe_fd[i - 1]);
				i--;
			}
			free(*pipe_fd);
			return (1);
		}
		i++;
	}
	i = 0;
	while (ac - 4 > i)
	{
		if (pipe((*pipe_fd)[i]) == -1)
			return (1);
		i++;
	}
	return (0);
}

void	pipex(char **av, int ac, char **env)
{
	int	**pipe_fd;
	int	i;

	if (open_pipes(ac, &pipe_fd) == 1)
		exit_handler("Failed to create pipe");
	i = 0;
	while (ac - 3 > i)
	{
		child_handler(av, ac, env, pipe_fd, i);
		i++;
	}
	close_fds(ac, pipe_fd);
	i = 0;
	while (ac - 3 > i)
	{
		if (wait(NULL) < 0)
			exit_handler("Failed to wait");
		i++;
	}
	i = 0;
	while (ac - 4 > i)
		free(pipe_fd[i++]);
	free(pipe_fd);
}
