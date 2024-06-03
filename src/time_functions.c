/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:06:07 by aldokezer         #+#    #+#             */
/*   Updated: 2024/06/03 10:43:01 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"


long int	ft_get_current_time(void)
{
	struct timeval	time;
	long			time_in_ms;

	gettimeofday(&time, NULL);
	time_in_ms = (long)(time.tv_sec * 1000 + time.tv_usec / 1000);
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


long	gettime(int time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (1);
	if (MILLISECOND == time_code)
		return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
	else if (MICROSECOND == time_code)
		return (tv.tv_sec * 1e6 + tv.tv_usec);
	else if (SECONDS == time_code)
		return (tv.tv_sec + tv.tv_usec / 1e6);
	else
		return (1337);
}

/*
 * HYBRID approach
 * given usleep is not precise
 * i usleep for majority of time ,
 * then refine wiht busy wait
*/
void	ft_precise_sleep(long period, t_philosopher *p)
{
	long	start;
	long	elapsed;
	long	rem;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < period)
	{
		if (p->resources->simulation_ended == true)
			break ;
		elapsed = gettime(MICROSECOND) - start;
		rem = period - elapsed;
		if (rem > 1e4)
			usleep(rem / 2);
		else
			while (gettime(MICROSECOND) - start < period)
				;
	}
}
