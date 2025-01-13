/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:34:26 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/13 09:18:32 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	loop_arg_identifier(t_args *args)
{
	int	i;

	i = 0;
	while (args->cmd_count - 1 > i)
	{
		ft_printf("pipe ");
		i++;
	}
	ft_printf("heredoc> ");
}

void	pipex_here_doc(t_args *args, int i)
{
	char	*str;

	if (pipe(args->pipe_fd[(i + 1) % 2]) < 0)
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
			return ;
		}
		if (ft_putstr_fd(str, args->pipe_fd[(i + 1) % 2][1]) < 0)
		{
			free(str);
			exit_handler(args, 1);
		}
		free(str);
	}
}
