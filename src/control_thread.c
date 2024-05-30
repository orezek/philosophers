/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:15:02 by aldokezer         #+#    #+#             */
/*   Updated: 2024/05/30 09:43:29 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"


void *ft_simulation_control(void *sim_void)
{
	//To do: implement
	t_simulation *simulation;
	simulation = (t_simulation *) sim_void;
	//(void)simulation;
	while (!simulation->resources->simulation_ended)
		printf("Control Thread\n");
	return (NULL);
}
