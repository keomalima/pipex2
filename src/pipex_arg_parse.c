/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_arg_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 18:03:20 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/05 11:48:39 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**parse_path_env(char **env)
{
	int		i;
	char	**path_env;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			path_env = ft_split(env[i] + 5, ':');
			if (!path_env)
				return (NULL);
			return (path_env);
		}
		i++;
	}
	return (NULL);
}

char	*get_exec_path(char **env, char *cmd)
{
	char	*prefixed_path;
	char	**path_env;
	int		i;

	path_env = parse_path_env(env);
	if (!path_env)
		return (NULL);
	i = 0;
	while (path_env[i])
	{
		prefixed_path = ft_join_path(path_env[i], cmd);
		if (!prefixed_path)
			break ;
		if (access(prefixed_path, X_OK) == 0)
		{
			free_split(path_env);
			return (prefixed_path);
		}
		free(prefixed_path);
		i++;
	}
	free_split(path_env);
	return (NULL);
}

char	**parse_arg(t_args *args, char *arg)
{
	char	*exec_path;
	char	**cmd;

	cmd = ft_split(arg, 32);
	if (!cmd)
		exit_handler(args, 12);
	exec_path = get_exec_path(args->env, cmd[0]);
	if (!exec_path)
	{
		ft_printf("Command not found: %s\n", cmd[0]);
		free_split(cmd);
		exit_handler(args, 0);
	}
	free(cmd[0]);
	cmd[0] = exec_path;
	return (cmd);
}
