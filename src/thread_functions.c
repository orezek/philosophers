/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:05:29 by aldokezer         #+#    #+#             */
/*   Updated: 2024/05/29 13:02:26 by aldokezer        ###   ########.fr       */
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

void	*ft_sim_execution(void *sim_struct)
{
	t_simulation *simulation;
	simulation = (t_simulation *) sim_struct;

	while (check_simulation_status(simulation))
	{
		ft_lock_forks(simulation);
		ft_eat_state(simulation);
		ft_release_forks(simulation);
		ft_sleep_state(simulation);
		ft_think_state(simulation);
	}
	printf("Simulation Ended:\n");
	return (NULL);
}
