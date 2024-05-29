/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 22:12:18 by aldokezer         #+#    #+#             */
/*   Updated: 2024/05/29 11:27:48 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philos.h"

// use static functions, static variables and function pointers

//cc main.c ./src/init_philosophers.c ./src/clean_allocs.c ./src/init_resources.c ./src/init_simulation.c -Wall -Wextra -Werror -o philos && ./philos

// states:

// eat - the state has condition to have two mutexes locked for a period of time
// sleep - state to keep the thread idle for certain period of time
// think - state in between sleep and eat without time period

int	philosophers(t_simulation *simulation)
{
	static int no_of_philos;
	static int	is_first;

	if (!simulation)
		return (-1);

	if (!is_first)
	{
		no_of_philos = simulation->resources->n_of_philosophers;
		is_first = 1;
	}
	else
		no_of_philos--;
	return (no_of_philos);
}

int	main(int argc, char *argv[])
{
	(void)argc;

	t_simulation *simulation;
	simulation = ft_malloc_simulation();
	ft_init_simulation(simulation, argv);

	int i = 0;
	printf("%ld\n", simulation->resources->sim_start_time);
	while ((philosophers(simulation)))
	{

		printf("Philosopher: %d and resource fork available: %d\n", simulation->philosophers[i].id, simulation->resources->forks[i]);
		i++;
	}
	ft_sleep(100);
	printf("End time: %ld\n", ft_get_current_time() - simulation->resources->sim_start_time);
	ft_clear_sim_memory(simulation);
	return (0);
}
