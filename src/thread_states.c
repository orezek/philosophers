/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_states.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:43:15 by aldokezer         #+#    #+#             */
/*   Updated: 2024/06/02 01:42:55 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

static void	ft_print_state(t_philosopher *p, char *message)
{
	long	philosopher_eat_start;

	pthread_mutex_lock(&p->resources->print_console_mtx);
	philosopher_eat_start = ft_get_sim_elapased_time(p->resources->sim_start_time);
	printf("%-10ld%-6d%s\n", philosopher_eat_start, p->id + 1, message);
	pthread_mutex_unlock(&p->resources->print_console_mtx);
}

void	ft_eat_state(t_philosopher *p)
{
	if (p->right_fork == HOLD && p->left_fork == HOLD)
	{
		pthread_mutex_lock(&p->resources->print_console_mtx);
		if (p->resources->simulation_ended)
		{
			pthread_mutex_unlock(&p->resources->print_console_mtx);
			return ;
		}
		pthread_mutex_unlock(&p->resources->print_console_mtx);
		ft_print_state(p, "is eating");
		pthread_mutex_lock(&p->eating_start_mtx);
		p->eating_start = ft_get_current_time();
		pthread_mutex_unlock(&p->eating_start_mtx);
		ft_sleep(p->resources->time_sleep);
		//ft_precise_sleep(p->resources->time_to_eat, p);
		pthread_mutex_lock(&p->no_meals_mtx);
		p->no_meals++;
		pthread_mutex_unlock(&p->no_meals_mtx);
		return ;
	}
	return ;
}

void	ft_sleep_state(t_philosopher *p)
{
	pthread_mutex_lock(&p->resources->print_console_mtx);
	if (p->resources->simulation_ended)
	{
		pthread_mutex_unlock(&p->resources->print_console_mtx);
		return ;
	}
	pthread_mutex_unlock(&p->resources->print_console_mtx);
	ft_print_state(p, "is sleeping");
	//ft_precise_sleep(p->resources->time_sleep, p);
	ft_sleep(p->resources->time_sleep);
}

void	ft_think_state(t_philosopher *p)
{
	pthread_mutex_lock(&p->resources->print_console_mtx);
	if (p->resources->simulation_ended)
	{
		pthread_mutex_unlock(&p->resources->print_console_mtx);
		return ;
	}
	pthread_mutex_unlock(&p->resources->print_console_mtx);
	ft_print_state(p, "is thinking");
}
