/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 21:58:59 by aldokezer         #+#    #+#             */
/*   Updated: 2024/06/01 23:29:37 by aldokezer        ###   ########.fr       */
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

	forks = ft_malloc_forks(simulation->resources->n_of_philosophers);
	i = 0;
	while (i < simulation->resources->n_of_philosophers)
	{
		forks[i]= AVAILABLE;
		i++;
	}
	return (forks);
}

static pthread_mutex_t *ft_malloc_mutexes(int n_of_philos)
{
	pthread_mutex_t *mutexes;

	mutexes = malloc(sizeof(pthread_mutex_t) * (n_of_philos));
	if (!mutexes)
		return (NULL);
	else
		return (mutexes);
}

void ft_init_resources(t_simulation *simulation)
{
	t_shared_resources *resources;

	resources = malloc(sizeof(t_shared_resources));
	if (!resources)
		exit(1);
	*resources = (t_shared_resources){0};
	simulation->resources = resources;
	resources->n_of_philosophers = 5; // Comes from args
	resources->forks = ft_init_forks(simulation);
	resources->forks_mtxs = ft_malloc_mutexes(simulation->resources->n_of_philosophers);
	resources->time_to_die = 800; // Comes from args;
	resources->time_to_eat = 200; // Comes from args;
	resources->time_sleep = 200; // Comes from args;
	resources->no_of_iterations = -1;
	resources->simulation_ended = false;
	resources->sim_start_time = ft_get_current_time();
}
