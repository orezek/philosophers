/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:24:35 by aldokezer         #+#    #+#             */
/*   Updated: 2024/05/29 11:32:19 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

t_simulation *ft_malloc_simulation(void)
{
	t_simulation *simulation;
	simulation = malloc(sizeof(t_simulation));
	if (!simulation)
		exit(1);
	return (simulation);
}

void ft_init_simulation(t_simulation *simulation, char *argv[])
{
	(void)argv;
	*simulation = (t_simulation){0}; // Initializes struct members to 0, NULL and 0.0
	ft_init_resources(simulation);
	ft_init_philosophres(simulation);
}
