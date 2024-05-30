/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_states.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:43:15 by aldokezer         #+#    #+#             */
/*   Updated: 2024/05/31 01:32:36 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

static void ft_print_state(t_philosopher *p, char *message)
{
	long philosopher_eat_start;
	philosopher_eat_start = ft_get_sim_elapased_time(p->resources->sim_start_time);
	printf("%-10ld%-6d%s\n", philosopher_eat_start, p->id, message);
}

int ft_eat_state(t_philosopher *p)
{
	if (p->right_fork == 1 && p->left_fork == 1)
	{
		pthread_mutex_lock(&p->resources->print_console_mtx);
		if (p->resources->simulation_ended)
		{
			pthread_mutex_unlock(&p->resources->print_console_mtx);
			return (0);
		}
		ft_print_state(p, "is eating");
		pthread_mutex_unlock(&p->resources->print_console_mtx);
		pthread_mutex_lock(&p->eating_start_mtx);
		p->eating_start = ft_get_current_time();
		pthread_mutex_unlock(&p->eating_start_mtx);
		ft_sleep(p->resources->time_to_eat);
		pthread_mutex_lock(&p->no_meals_mtx);
		p->no_meals++;
		pthread_mutex_unlock(&p->no_meals_mtx);
	}
	return(0);
}

int ft_sleep_state(t_philosopher *p)
{
	if (!p->resources->simulation_ended)
	{
		pthread_mutex_lock(&p->resources->print_console_mtx);
		ft_print_state(p, "is sleeping");
		pthread_mutex_unlock(&p->resources->print_console_mtx);
		ft_sleep(p->resources->time_sleep);
	}
	return(0);
}

int ft_think_state(t_philosopher *p)
{
	if (!p->resources->simulation_ended)
	{
		pthread_mutex_lock(&p->resources->print_console_mtx);
		ft_print_state(p, "is thinking");
		pthread_mutex_unlock(&p->resources->print_console_mtx);
		ft_sleep(p->resources->time_sleep);
	}
	return(0);
}
