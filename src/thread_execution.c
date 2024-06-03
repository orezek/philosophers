/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:05:29 by aldokezer         #+#    #+#             */
/*   Updated: 2024/06/03 00:21:32 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

static int check_simulation_status(t_simulation *simulation)
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
	t_philosopher *philosopher;
	philosopher = (t_philosopher *) phil_struct;

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
