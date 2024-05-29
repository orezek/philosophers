/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_states.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:43:15 by aldokezer         #+#    #+#             */
/*   Updated: 2024/05/29 21:38:08 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

int ft_eat_state(t_philosopher *philosopher)
{
	(void)philosopher;
	printf("Eating\n");
	//ft_sleep(100);
	return(0);
}

int ft_sleep_state(t_philosopher *philosopher)
{
	(void)philosopher;
	printf("Sleeping\n");
	//ft_sleep(100);
	return(0);
}

int ft_think_state(t_philosopher *philosopher)
{
	(void)philosopher;
	printf("Thinking\n");
	//ft_sleep(100);
	return(0);
}
