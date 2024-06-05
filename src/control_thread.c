/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:15:02 by aldokezer         #+#    #+#             */
/*   Updated: 2024/06/05 17:28:13 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

static void	ft_print_state_control_thread(t_philosopher *p, char *message)
{
	long	philosopher_eat_start;

	philosopher_eat_start = ft_get_sim_elapased_time
		(p->resources->sim_start_time);
	printf("%-10ld%-6d%s\n", philosopher_eat_start, p->id + 1, message);
}

static bool	is_time_to_die_exceeded(t_simulation *simulation)
{
	int				i;
	t_philosopher	*p;

	i = 0;
	while (i < simulation->resources->n_of_philosophers)
	{
		p = &simulation->philosophers[i];
		pthread_mutex_lock(&p->eating_start_mtx);
		if (ft_get_current_time() - p->eating_start > p->resources->time_to_die)
		{
			pthread_mutex_unlock(&p->eating_start_mtx);
			pthread_mutex_lock(&p->resources->print_console_mtx);
			simulation->resources->simulation_ended = true;
			ft_print_state_control_thread(p, "died");
			pthread_mutex_unlock(&p->resources->print_console_mtx);
			return (true);
		}
		pthread_mutex_unlock(&p->eating_start_mtx);
		i++;
	}
	return (false);
}

static bool	is_execution_complete(t_simulation *simulation)
{
	int				i;
	t_philosopher	*p;

	i = 0;
	while (i < simulation->resources->n_of_philosophers)
	{
		p = &simulation->philosophers[i];
		pthread_mutex_lock(&p->no_meals_mtx);
		if (p->no_meals > simulation->resources->no_of_iterations + 1)
		{
			pthread_mutex_unlock(&p->no_meals_mtx);
			pthread_mutex_lock(&p->resources->print_console_mtx);
			simulation->resources->simulation_ended = true;
			pthread_mutex_unlock(&p->resources->print_console_mtx);
			return (true);
		}
		pthread_mutex_unlock(&p->no_meals_mtx);
		i++;
	}
	return (false);
}

void	*ft_simulation_control(void *sim_void)
{
	t_simulation	*simulation;

	simulation = (t_simulation *) sim_void;
	while (1)
	{
		if (is_time_to_die_exceeded(simulation))
			return (NULL);
		if (simulation->resources->no_of_iterations != IGNORE)
		{
			if (is_execution_complete(simulation))
				return (NULL);
		}
	}
	return (NULL);
}
