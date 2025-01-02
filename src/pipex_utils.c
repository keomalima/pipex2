/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 18:01:41 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/02 20:01:33 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	print_err_msg(const char *err_msg)
{
	if (errno != 0)
		ft_printf("%s: %s\n", strerror(errno), err_msg);
	else
		ft_printf("%s\n", err_msg);
}

char	**parse_path_env(t_filed *fd)
{
	char	**path;
	int		i;

	path = NULL;
	i = 0;
	while (fd->env[i])
	{
		if (ft_strnstr(fd->env[i], "PATH=", 5))
		{
			path = ft_split(fd->env[i] + 5, ':');
			if (!path)
				print_err_msg("Failed to split dir paths");
			return (path);
		}
		i++;
	}
	print_err_msg("PATH env variable not found");
	free_split(path);
	return (NULL);
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
}