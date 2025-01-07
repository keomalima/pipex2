/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 18:01:41 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/07 10:56:07 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	initialize_variables(int ac, char **av, char **env, t_args *args)
{
	args->here_doc = ft_strncmp(av[1], "here_doc", 8) == 0;
	args->cmd_count = ac - 3 - args->here_doc;
	args->ac = ac;
	args->av = av;
	args->env = env;
	args->cmd = NULL;
}

void	open_pipes(t_args *args, int pipe_fd[2][2])
{
	if (pipe(pipe_fd[0]) == -1)
		exit_handler(args, 1);
	if (pipe(pipe_fd[1]) == -1)
		exit_handler(args, 1);
}

void	close_fds(int fd[2][2])
{
	if (fd[0][0] >= 0)
		close(fd[0][0]);
	if (fd[0][1] >= 0)
		close(fd[0][1]);
	if (fd[1][0] >= 0)
		close(fd[1][0]);
	if (fd[1][1] >= 0)
		close(fd[1][1]);
}

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	arr = NULL;
}

void	exit_handler(t_args *args, int err_code)
{
	if (args->cmd)
		free_split(args->cmd);
	if (err_code == 0)
	{
		err_code = 1;
		errno = 0;
	}
	if (err_code == 127)
		errno = 0;
	if (err_code == 12)
		errno = ENOMEM;
	if (errno)
		perror("Error");
	exit(err_code);
}
