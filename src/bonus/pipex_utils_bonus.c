/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 18:01:41 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/10 11:36:18 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	open_pipes(t_args *args)
{
	if (pipe(args->pipe_fd[0]) == -1)
		exit_handler(args, 1);
	if (pipe(args->pipe_fd[1]) == -1)
		exit_handler(args, 1);
}

void	close_fds(t_args *args)
{
	if (args->pipe_fd[0][0] >= 0)
		close(args->pipe_fd[0][0]);
	if (args->pipe_fd[0][1] >= 0)
		close(args->pipe_fd[0][1]);
	if (args->pipe_fd[1][0] >= 0)
		close(args->pipe_fd[1][0]);
	if (args->pipe_fd[1][1] >= 0)
		close(args->pipe_fd[1][1]);
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
	close_fds(args);
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
