/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 11:57:42 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/03 15:51:30 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char **av, char **env)
{
	if (ac == 5)
		pipex(av, ac, env);
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

