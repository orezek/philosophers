/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:05:29 by aldokezer         #+#    #+#             */
/*   Updated: 2024/06/07 16:29:28 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

void	ft_print_eaten_meals(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->resources->print_console_mtx);
	printf("P: id: %d, No_of_meals: %d\n",
		philosopher->id, philosopher->no_meals);
	pthread_mutex_unlock(&philosopher->resources->print_console_mtx);
}

static int	check_simulation_status(t_simulation *simulation)
{
	pthread_mutex_lock(&simulation->resources->print_console_mtx);
	if (simulation->resources->simulation_ended)
	{
		pthread_mutex_unlock(&simulation->resources->print_console_mtx);
		return (false);
	}
	else
	{
		pthread_mutex_unlock(&simulation->resources->print_console_mtx);
		return (true);
	}
}

void	*ft_sim_execution(void *phil_struct)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *) phil_struct;
	while (true)
	{
		usleep(5);
		pthread_mutex_lock(&philosopher->resources->threads_ready_mtx);
		if (philosopher->resources->threads_ready == true)
		{
			pthread_mutex_unlock(&philosopher->resources->threads_ready_mtx);
			break ;
		}
		pthread_mutex_unlock(&philosopher->resources->threads_ready_mtx);
	}
	while (check_simulation_status(philosopher->simulation))
	{
		ft_lock_forks(philosopher);
		ft_eat_state(philosopher);
		ft_release_forks(philosopher);
		ft_sleep_state(philosopher);
		ft_think_state(philosopher);
	}
	return (NULL);
}
