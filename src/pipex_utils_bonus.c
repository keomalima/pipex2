/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 18:01:41 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/05 17:02:37 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	initialize_variables(int ac, char **av, char **env, t_args *args)
{
	args->cmd_count = ac - 3;
	args->pipe_count = ac - 4;
	args->av = av;
	args->env = env;
	args->cmd = NULL;
	args->pipe_fd = NULL;
}

char	*ft_join_path(const char *s1, const char *s2)
{
	char	*str;
	int		i;
	int		j;
	int		add_slash;

	if (!s1 || !s2)
		return (NULL);
	add_slash = (s1[ft_strlen(s1) - 1] != '/');
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + add_slash + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	if (add_slash)
		str[j++] = '/';
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

void	wait_children(t_args *args)
{
	int	i;
	int	status;

	i = 0;
	while (args->cmd_count > i)
	{
		if (waitpid(-1, &status, 0) < 0)
			exit_handler(args, 1);
		i++;
	}
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
	if (args->pipe_fd)
		free_pipe_fds(args);
	if (err_code == 0)
		errno = 0;
	if (err_code == 12)
		errno = ENOMEM;
	if (errno)
		perror("Error");
	exit(EXIT_FAILURE);
}
