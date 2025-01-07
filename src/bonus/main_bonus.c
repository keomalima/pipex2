/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:24:02 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/07 10:36:35 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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
