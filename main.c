/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 22:12:18 by aldokezer         #+#    #+#             */
/*   Updated: 2024/05/30 10:15:14 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philos.h"

// use static functions, static variables and function pointers

//cc main.c ./src/init_philosophers.c ./src/clean_allocs.c ./src/init_resources.c ./src/init_simulation.c ./src/time_functions.c ./src/thread_functions.c ./src/thread_states.c ./src/forks.c  -Wall -Wextra -Werror -o philos && ./philos


// states:

// eat - the state has condition to have two mutexes locked for a period of time
// sleep - state to keep the thread idle for certain period of time
// think - state in between sleep and eat without time period

// To do!!
// void	destroy_mutexes(t_simulation *simulation)
// {
// 	int	i;

// 	i = 0;
// 	while (i < simulation->resources->n_of_philosophers)
// 	{
// 		//pthread_mutex_destroy(&dinner->shared->forks_mtxs[i]);
// 		pthread_mutex_destroy(&simulation->philosophers[i].eating_start_time_mtx);
// 		pthread_mutex_destroy(&dinner->philos[i].nof_meals_mtx);
// 		i++;
// 	}
// 	pthread_mutex_destroy(&dinner->shared->printf_mtx);
// }

bool	threads_to_run(t_simulation *simulation)
{
	static int no_of_philos;

	if (!simulation)
		return (false);
	if (no_of_philos < simulation->resources->n_of_philosophers)
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

int	main(int argc, char *argv[])
{
	(void)argc;
	t_simulation *simulation;
	t_philosopher *philosopher;
	int i;

	simulation = ft_malloc_simulation();
	ft_init_simulation(simulation, argv);
	ft_init_mutexes(simulation);
	i = 0;
	while ((threads_to_run(simulation)))
	{
		philosopher = &simulation->philosophers[i];
		pthread_create(&philosopher->thread, NULL, &ft_sim_execution, philosopher);
		i++;
	}
	pthread_create(&simulation->control_thread, NULL, &ft_simulation_control, simulation);
	i = 0;
	while (threads_to_run(simulation))
		pthread_join(simulation->philosophers[i++].thread, NULL);
	pthread_join(simulation->control_thread, NULL);
	ft_clear_mutexes(simulation);
	ft_clear_sim_memory(simulation);
	return (0);
}
