/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 18:06:56 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/10 12:03:19 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int is_fd_open(int fd)
{
    if (fcntl(fd, F_GETFD) == -1)
    {
        if (errno == EBADF)
            return 0;
    }
    return 1;
}

void	switch_io_n_execve(t_args *args, int i, int in_fd, int out_fd)
{
	args->child_pids[i] = fork();
	if (args->child_pids[i] < 0)
		exit_handler(args, -1);
	if (args->child_pids[i] == 0)
	{
		args->cmd = parse_arg(args, args->av[i + 2 + args->here_doc]);
		if (dup2(in_fd, STDIN_FILENO) == -1)
			exit_handler(args, 1);
		close(in_fd);
		if (dup2(out_fd, STDOUT_FILENO) == -1)
			exit_handler(args, 1);
		close(out_fd);
		if (execve(args->cmd[0], args->cmd, args->env) == -1)
			exit_handler(args, 1);
	}
}

void	open_files(t_args *args, int i, int *file_fd)
{
	if (i == 0)
	{
		*file_fd = open(args->av[1], O_RDONLY);
		if (*file_fd < 0)
		{
			if (access(args->av[1], R_OK ) < 0 && access(args->av[1], F_OK ) == 0 )
				ft_printf("permission denied: %s \n", args->av[1]);
			else
				ft_printf("no such file or directory: %s\n", args->av[1]);
		}
	}
	else
	{
		*file_fd = open(args->av[args->ac - 1],
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*file_fd < 0)
			ft_printf("permission denied: %s\n",
			args->av[args->cmd_count + 2]);
	}
	if (*file_fd < 0)
		exit_handler(args, -1);
}

void	set_up_fd(t_args *args, int i)
{
	int	fd_in;
	int	fd_out;

	if (i == 0)
	{
		if (args->here_doc)
			fd_in = pipex_here_doc(args);
		else
			open_files(args, i, &fd_in);
		fd_out = args->pipe_fd[i % 2][1];
	}
	else if (i == args->cmd_count - 1)
	{
		fd_in = args->pipe_fd[(i + 1) % 2][0];
		open_files(args, i, &fd_out);
		close(args->pipe_fd[i % 2][0]);
		close(args->pipe_fd[i % 2][1]);
	}
	else
	{
		fd_in = args->pipe_fd[(i + 1) % 2][0];
		fd_out = args->pipe_fd[i % 2][1];
	}
	if (fd_in < 0 || fd_out < 0)
		exit_handler(args, -1);
	switch_io_n_execve(args, i, fd_in, fd_out);
	close(fd_in);
	close(fd_out);
}

void	pipex(t_args *args)
{
	int	i;
	int	status;

	args->child_pids = malloc (args->cmd_count * sizeof(pid_t));
	if (!args->child_pids)
		exit_handler(args, 1);
	i = 0;
	while (args->cmd_count > i)
	{
		if (pipe(args->pipe_fd[i % 2]) < 0)
			exit_handler(args, 1);
		set_up_fd(args, i);
		close(args->pipe_fd[i % 2][1]);
		i++;
	}
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
