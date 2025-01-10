/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:24:02 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/10 09:39:35 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	initialize_variables(int ac, char **av, char **env, t_args *args)
{
	args->here_doc = ft_strncmp(av[1], "here_doc", 8) == 0;
	args->cmd_count = ac - 3 - args->here_doc;
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

	if (ac > 4 && env)
	{
		initialize_variables(ac, av, env, &args);
		pipex(&args);
	}
	else
	{
		ft_printf("Error: Too few arguments\n");
		return (1);
	}
	return (0);
}
