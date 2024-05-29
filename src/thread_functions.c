/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:05:29 by aldokezer         #+#    #+#             */
/*   Updated: 2024/05/29 21:37:46 by aldokezer        ###   ########.fr       */
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

	printf("Thread id: %d\n", philosopher->id);

	while (check_simulation_status(philosopher->simulation))
	{
		ft_lock_forks(philosopher);
		ft_eat_state(philosopher);
		ft_release_forks(philosopher);
		ft_sleep_state(philosopher);
		ft_think_state(philosopher);
		philosopher->simulation->resources->simulation_ended = true;
	}
	printf("Simulation Ended:\n");
	return (NULL);
}
