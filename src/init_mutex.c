/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:51:10 by aldokezer         #+#    #+#             */
/*   Updated: 2024/06/02 21:18:47 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

void	ft_init_mutexes(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->resources->n_of_philosophers)
	{
		pthread_mutex_init(&simulation->resources->forks_mtxs[i], NULL);
		pthread_mutex_init(&simulation->philosophers[i].eating_start_mtx, NULL);
		pthread_mutex_init(&simulation->philosophers[i].no_meals_mtx, NULL);
		i++;
	}
	pthread_mutex_init(&simulation->resources->print_console_mtx, NULL);
	pthread_mutex_init(&simulation->resources->sim_ended_mtx, NULL);
}


void	ft_clear_mutexes(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->resources->n_of_philosophers)
	{
		pthread_mutex_destroy(&simulation->resources->forks_mtxs[i]);
		pthread_mutex_destroy(&simulation->philosophers[i].eating_start_mtx);
		pthread_mutex_destroy(&simulation->philosophers[i].no_meals_mtx);
		i++;
	}
	pthread_mutex_destroy(&simulation->resources->print_console_mtx);
}
