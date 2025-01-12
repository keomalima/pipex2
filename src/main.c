/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 11:57:42 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/12 11:45:39 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	initialize_variables(int ac, char **av, char **env, t_args *args)
{
	args->cmd_count = ac - 3;
	args->ac = ac;
	args->av = av;
	args->env = env;
	args->cmd = NULL;
	args->child_pids = NULL;
	args->pipe_fd[0][0] = -1;
	args->pipe_fd[0][1] = -1;
	args->pipe_fd[1][0] = -1;
	args->pipe_fd[1][1] = -1;
}

int	main(int ac, char **av, char **env)
{
	t_args	args;

	if (ac == 5 && env)
	{
		initialize_variables(ac, av, env, &args);
		pipex(&args);
	}
	else
	{
		if (ac > 5)
			ft_printf("Error: Too many arguments\n");
		else
			ft_printf("Error: Too few arguments\n");
		return (1);
	}
	return (0);
}
