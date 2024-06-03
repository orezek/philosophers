/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_allocs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 21:01:29 by aldokezer         #+#    #+#             */
/*   Updated: 2024/06/03 23:18:16 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

void	ft_clear_sim_memory(t_simulation *simulation)
{
	if (simulation->philosophers)
	{
		free(simulation->philosophers);
	}
	if (simulation->resources)
	{
		if (simulation->resources->forks)
		{
			free(simulation->resources->forks);
			free(simulation->resources->forks_mtxs);
		}
		free(simulation->resources);
	}
	free(simulation);
}
