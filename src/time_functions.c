/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:06:07 by aldokezer         #+#    #+#             */
/*   Updated: 2024/05/29 11:07:21 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"


long int	ft_get_current_time(void)
{
	struct timeval	time;
	long			time_in_ms;

	gettimeofday(&time, NULL);
	time_in_ms = (long)(time.tv_sec * 1E3 + time.tv_usec / 1E3);
	return (time_in_ms);
}

long ft_get_sim_elapased_time(long sim_start_time)
{
	return (ft_get_current_time() - sim_start_time);
}

void	ft_sleep(long period)
{
	long	init_time;

	init_time = ft_get_current_time();
	while ((ft_get_current_time() - init_time) < period)
		usleep(10);
}
