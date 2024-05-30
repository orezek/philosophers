/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:34:05 by aldokezer         #+#    #+#             */
/*   Updated: 2024/05/30 10:07:40 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

static t_philosopher *ft_malloc_philosophers(int n_of_philos)
{
	t_philosopher *philosophers;

	philosophers = malloc(sizeof(t_philosopher) * (n_of_philos));
	if (!philosophers)
		return (NULL);
	else
		return (philosophers);
}

void ft_init_philosophres(t_simulation *simulation)
{
	t_philosopher *philosophers;
	int i;

	philosophers = ft_malloc_philosophers(simulation->resources->n_of_philosophers);
	if (!philosophers)
		return ;
	simulation->philosophers = philosophers;
	i = 0;
	while (i < simulation->resources->n_of_philosophers)
	{
		philosophers[i] = (t_philosopher){0};
		simulation->philosophers[i].id = i + 1;
		simulation->philosophers[i].eating_start = ft_get_current_time();
		simulation->philosophers[i].right_fork = 0;
		simulation->philosophers[i].left_fork = 0;
		simulation->philosophers[i].no_meals = 0;
		simulation->philosophers[i].resources = simulation->resources;
		simulation->philosophers[i].simulation = simulation;
		i++;
	}
	return ;
}
