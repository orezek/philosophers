/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 22:12:18 by aldokezer         #+#    #+#             */
/*   Updated: 2024/06/03 21:59:52 by aldokezer        ###   ########.fr       */
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


static int ft_parse_input(t_simulation *s, int argc, char **argv)
{
	if (check_args(argc, argv))
	{
		ft_clear_mutexes(s);
		ft_clear_sim_memory(s);
		return (1);
	}
	else
	{
		if (argc > 1 && argc < 6)
		{
			s->resources->n_of_philosophers = ft_int_atoi(argv[1]);
			s->resources->time_to_die = ft_int_atoi(argv[2]);
			s->resources->time_to_eat = ft_int_atoi(argv[3]);
			s->resources->time_sleep = ft_int_atoi(argv[4]);
		}
		if (argc == 6)
		{
			s->resources->n_of_philosophers = ft_int_atoi(argv[1]);
			s->resources->time_to_die = ft_int_atoi(argv[2]);
			s->resources->time_to_eat = ft_int_atoi(argv[3]);
			s->resources->time_sleep = ft_int_atoi(argv[4]);
			s->resources->no_of_iterations = ft_int_atoi(argv[5]);
		}
		return (0);
	}

}

static int	dining_philosphers(int argc, char *argv[])
{
	t_simulation	*sim;
	t_philosopher	*p;
	int				i;
	(void)argc;
	sim = ft_malloc_simulation();
	ft_init_simulation(sim, argv);
	if (ft_parse_input(sim, argc, argv))
		return (1);
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
