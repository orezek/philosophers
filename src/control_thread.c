/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:15:02 by aldokezer         #+#    #+#             */
/*   Updated: 2024/05/30 19:10:03 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"


void *ft_simulation_control(void *sim_void)
{
	int i;
	t_simulation *simulation;
	simulation = (t_simulation *) sim_void;
	i = 0;
	pthread_mutex_lock(&simulation->resources->print_console_mtx);
	while (i < 10)
	{
		printf("Control Thread : %d\n", i);
		i++;
	}
	pthread_mutex_unlock(&simulation->resources->print_console_mtx);
	return (NULL);
}
