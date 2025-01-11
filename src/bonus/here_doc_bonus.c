/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:34:26 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/11 22:14:04 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	loop_arg_identifier(t_args *args)
{
	int	i;

	i = -1;
	while (args->cmd_count > ++i)
		ft_printf("pipe ");
	ft_printf("heredoc> ");
}

void	failed_putstr(t_args *args, char *str, int fd[2])
{
	free(str);
	close(fd[0]);
	close(fd[1]);
	exit_handler(args, 1);
}

int	pipex_here_doc(t_args *args)
{
	int		fd[2];
	char	*str;

	if (pipe(fd) < 0)
		exit_handler(args, 1);
	while (1)
	{
		loop_arg_identifier(args);
		str = get_next_line(STDIN_FILENO);
		if (!str)
			exit_handler(args, 1);
		if (ft_strncmp(str, args->av[2], ft_strlen(args->av[2])) == 0)
		{
			free(str);
			break ;
		}
		if (ft_putstr_fd(str, fd[1]) < 0)
			failed_putstr(args, str, fd);
		free(str);
	}
	close(fd[1]);
	return (fd[0]);
}
