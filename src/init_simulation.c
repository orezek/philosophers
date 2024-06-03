/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:24:35 by aldokezer         #+#    #+#             */
/*   Updated: 2024/06/03 23:07:32 by aldokezer        ###   ########.fr       */
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

void ft_init_simulation(t_simulation *simulation, int argc, char *argv[])
{
	*simulation = (t_simulation){0};
	ft_init_resources(simulation, argc, argv);
	ft_init_philosophres(simulation);
	ft_init_mutexes(simulation);
}
