/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 18:01:41 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/12 11:44:00 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_fd(t_args *args, int *fd)
{
	if (*fd >= 0)
	{
		if (close(*fd) < 0)
			exit_handler(args, 1);
		*fd = -1;
	}
}

void	close_all_fds(t_args *args)
{
	int	i;

	i = 0;
	while (2 > i)
	{
		close_fd(args, &args->pipe_fd[i][0]);
		close_fd(args, &args->pipe_fd[i][1]);
		i++;
	}
}

void	free_nsplit(char **tab, int index)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (index > i)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
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
	close_all_fds(args);
	if (args->cmd)
		free_split(args->cmd);
	if (args->child_pids)
		free(args->child_pids);
	if (err_code == -1)
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
