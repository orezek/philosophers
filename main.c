/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 22:12:18 by aldokezer         #+#    #+#             */
/*   Updated: 2024/06/04 14:16:17 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

/*
############Testing#################
General note:
Inrease the argument "time_to_die" generously as the
profilers decrease the speed of the thread execution.
For monitoring data races, deadlocks or memeory leaks
you do not need to check thread sychornization
(time_to_die) after all!

Data races and deadlock checks
1) compile with flag -fsanitize=thread and run
or
2) remove the flag from above and run
valgrind --tool=helgrind --fair-sched=yes
./philo 5 50000 200 200 10
valgrind --tool=helgrind --fair-sched=yes
--history-level=approx ./philo 5 50000 200 200 10
valgrind --tool=helgrind --fair-sched=yes
--history-level=none ./philo 5 50000 200 200 10
or
3) run
valgrind --tool=drd --fair-sched=yes ./philo 5 50000 200 200 10

Memory leaks cheks
valgrind ./philo 5 50000 200 200 10

*/

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

static int	dining_philosphers(int argc, char *argv[])
{
	t_simulation	*sim;
	t_philosopher	*p;
	int				i;

	if (check_args(argc, argv))
		return (1);
	sim = ft_malloc_simulation();
	ft_init_simulation(sim, argc, argv);
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
	return (0);
}

int	main(int argc, char *argv[])
{
	if (dining_philosphers(argc, argv))
		return (1);
	return (0);
}
