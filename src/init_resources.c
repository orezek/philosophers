/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 21:58:59 by aldokezer         #+#    #+#             */
/*   Updated: 2024/05/29 09:42:44 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

static int *ft_malloc_forks(int n_of_philos)
{
	int *forks;

	forks = malloc(sizeof(int) * (n_of_philos));
	if (!forks)
		return (NULL);
	else
		return (forks);
}

static int *ft_init_forks(t_simulation *simulation)
{
	int	*forks;
	int	i;

	forks = ft_malloc_forks(simulation->n_of_philosophers);
	i = 0;
	while (i < simulation->n_of_philosophers)
	{
		forks[i]= AVAILABLE;
		i++;
	}
	return (forks);
}

void ft_init_resources(t_simulation *simulation)
{
	t_shared_resources *resources;

	resources = malloc(sizeof(t_shared_resources));
	if (!resources)
		exit(1);
	resources->forks = ft_init_forks(simulation);
	simulation->resources = resources;
	simulation->resources->simulation_ended = false;
	simulation->resources->sim_start_time = ft_get_current_time();
}
