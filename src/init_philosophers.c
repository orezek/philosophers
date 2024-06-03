/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:34:05 by aldokezer         #+#    #+#             */
/*   Updated: 2024/06/03 23:27:48 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

static t_philosopher	*ft_malloc_philosophers(int n_of_philos)
{
	t_philosopher	*philosophers;

	philosophers = malloc(sizeof(t_philosopher) * (n_of_philos));
	if (!philosophers)
		return (NULL);
	else
		return (philosophers);
}

void	ft_init_philosophres(t_simulation *sim)
{
	t_philosopher	*philosophers;
	int				i;

	philosophers = ft_malloc_philosophers(sim->resources->n_of_philosophers);
	if (!philosophers)
		return ;
	sim->philosophers = philosophers;
	i = 0;
	while (i < sim->resources->n_of_philosophers)
	{
		philosophers[i] = (t_philosopher){0};
		sim->philosophers[i].id = i;
		sim->philosophers[i].eating_start = ft_get_current_time();
		sim->philosophers[i].right_fork = RELEASE;
		sim->philosophers[i].left_fork = RELEASE;
		sim->philosophers[i].no_meals = 0;
		sim->philosophers[i].resources = sim->resources;
		sim->philosophers[i].simulation = sim;
		i++;
	}
	return ;
}
