/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_states.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:43:15 by aldokezer         #+#    #+#             */
/*   Updated: 2024/05/30 08:24:05 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

int ft_eat_state(t_philosopher *philosopher)
{
	(void)philosopher;
	printf("Phil: %d is Eating\n", philosopher->id);
	//ft_sleep(100);
	return(0);
}

int ft_sleep_state(t_philosopher *philosopher)
{
	(void)philosopher;
	printf("Phil: %d is Sleeping\n", philosopher->id);
	//ft_sleep(100);
	return(0);
}

int ft_think_state(t_philosopher *philosopher)
{
	(void)philosopher;
	printf("Phil: %d is Thinking\n", philosopher->id);
	//ft_sleep(100);
	return(0);
}
