/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 11:57:42 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/05 16:14:03 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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