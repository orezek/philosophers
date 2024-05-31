/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:05:29 by aldokezer         #+#    #+#             */
/*   Updated: 2024/05/31 20:03:24 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

static int check_simulation_status(t_simulation *simulation)
{
	if (simulation->resources->simulation_ended)
		return (0);
	else
		return (1);
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
	// pthread_mutex_lock(&philosopher->resources->print_console_mtx);
	// printf("Thread id: %d Ended: %d, %d, %d\n", philosopher->id, philosopher->no_meals, philosopher->left_fork, philosopher->right_fork);
	// pthread_mutex_unlock(&philosopher->resources->print_console_mtx);
	return (NULL);
}
