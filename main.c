/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 22:12:18 by aldokezer         #+#    #+#             */
/*   Updated: 2024/06/03 20:31:28 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

// use static functions, static variables and function pointers

bool	threads_to_run(t_simulation *sim)
{
	static int	no_of_philos;

	if (!sim)
		return (false);
	if (no_of_philos < sim->resources->n_of_philosophers)
	{
		no_of_philos++;
		return (true);
	}
	else
	{
		no_of_philos = 0;
		return (false);
	}
}

static void	ft_sync_threads(t_simulation *sim)
{
	pthread_mutex_lock(&sim->resources->threads_ready_mtx);
	sim->resources->sim_start_time = ft_get_current_time();
	sim->resources->threads_ready = true;
	pthread_mutex_unlock(&sim->resources->threads_ready_mtx);
}

static void	dining_philosphers(int argc, char *argv[])
{
	t_simulation	*sim;
	t_philosopher	*p;
	int				i;

	(void)argc;
	sim = ft_malloc_simulation();
	ft_init_simulation(sim, argv);
	i = -1;
	while ((threads_to_run(sim)))
	{
		p = &sim->philosophers[++i];
		pthread_create(&p->thread, NULL, &ft_sim_execution, p);
	}
	ft_sync_threads(sim);
	pthread_create(&sim->control_thread, NULL, &ft_simulation_control, sim);
	i = -1;
	while (threads_to_run(sim))
		pthread_join(sim->philosophers[++i].thread, NULL);
	pthread_join(sim->control_thread, NULL);
	ft_clear_mutexes(sim);
	ft_clear_sim_memory(sim);
}

int	main(int argc, char *argv[])
{
	dining_philosphers(argc, argv);
	return (0);
}
