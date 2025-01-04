/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 11:57:42 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/04 12:48:07 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char **av, char **env)
{
	t_args	args;

	if (ac > 4 && env)
	{
		args.cmd_count = ac - 3;
		args.pipe_count = ac - 4;
		args.av = av;
		args.env = env;
		args.cmd = NULL;
		args.pipe_fd = NULL;
		pipex(&args);
	}
	else
	{
		if (ac > 6)
			ft_printf("Error: Too many arguments\n");
		else
			ft_printf("Error: Too few arguments\n");
		return (1);
	}
	return (0);
}
