/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_arg_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 18:03:20 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/02 18:01:05 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*get_exec_path(char **path, char *prefixed_cmd)
{
	char	*file_path;
	int		i;

	i = 0;
	while (path[i])
	{
		file_path = ft_strjoin(path[i], prefixed_cmd);
		if (!file_path)
		{
			print_err_msg("Failed to append file_path");
			return (NULL);
		}
		if (access(file_path, X_OK) == 0)
		{
			free(prefixed_cmd);
			return (file_path);
		}
		free(file_path);
		i++;
	}
	ft_printf("Command not found: %s\n", (prefixed_cmd + 1));
	return (NULL);
}

char	**parse_arg(char *args, char **path_env)
{
	char	*prefixed_cmd;
	char	**cmd;

	cmd = ft_split(args, 32);
	if (!cmd)
	{
		print_err_msg("Failed to split cmd args string\n");
		return (NULL);
	}
	prefixed_cmd = ft_strjoin("/", cmd[0]);
	if (!prefixed_cmd)
	{
		free_split(cmd);
		print_err_msg("Failed to prefix the cmd\n");
		return (NULL);
	}
	free(cmd[0]);
	cmd[0] = get_exec_path(path_env, prefixed_cmd);
	if (!cmd[0])
	{
		free(prefixed_cmd);
		free_split(cmd);
		return (NULL);
	}
	return (cmd);
}
