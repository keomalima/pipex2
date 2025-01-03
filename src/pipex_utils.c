/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 18:01:41 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/03 14:21:59 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

void	close_fds(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
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

void	exit_handler(const char *err_msg)
{
	if (!err_msg)
		ft_printf("%s\n", err_msg);
	else
		ft_printf("%s: %s\n", strerror(errno), err_msg);
	exit(EXIT_FAILURE);
}
