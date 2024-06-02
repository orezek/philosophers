/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:45:57 by aldokezer         #+#    #+#             */
/*   Updated: 2024/06/02 21:48:37 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

static void ft_print_fork_status(t_philosopher *p, Side fork)
{
	long fork_time;
	fork_time = ft_get_current_time() - p->resources->sim_start_time;
	pthread_mutex_lock(&p->resources->print_console_mtx);
	if (fork == RIGHT_FORK)
		printf("%-10ld%-6dhas taken a fork\n", fork_time, p->id + 1);
	else if (fork == LEFT_FORK)
		printf("%-10ld%-6dhas taken a fork\n", fork_time, p->id + 1);
	pthread_mutex_unlock(&p->resources->print_console_mtx);
}

inline static int get_right_fork_index(t_philosopher *p)
{
	return ((p->id + 1) % p->resources->n_of_philosophers);
}

int	ft_lock_left_fork(t_philosopher *p)
{
	while (true)
	{
		pthread_mutex_lock(&p->resources->sim_ended_mtx);
		if (p->resources->simulation_ended)
		{
			pthread_mutex_unlock(&p->resources->sim_ended_mtx);
			return (0);
		}
		pthread_mutex_unlock(&p->resources->sim_ended_mtx);
		pthread_mutex_lock(&p->resources->forks_mtxs[p->id]);
		if (p->resources->forks[p->id] == AVAILABLE)
		{
			p->resources->forks[p->id] = TAKEN;
			p->left_fork = HOLD;
			pthread_mutex_unlock(&p->resources->forks_mtxs[p->id]);
			pthread_mutex_lock(&p->resources->sim_ended_mtx);
			if (p->resources->simulation_ended == false)
			{
				pthread_mutex_unlock(&p->resources->sim_ended_mtx);
				ft_print_fork_status(p, LEFT_FORK);
			}
			else
				pthread_mutex_unlock(&p->resources->sim_ended_mtx);
			return (0);
		}
		pthread_mutex_unlock(&p->resources->forks_mtxs[p->id]);
		//sched_yield();
	}
}

int	ft_lock_right_fork(t_philosopher *p)
{
	int	right_fork_index;

	right_fork_index = get_right_fork_index(p);

	while (true)
	{
		pthread_mutex_lock(&p->resources->sim_ended_mtx);
		if (p->resources->simulation_ended)
		{
			pthread_mutex_unlock(&p->resources->sim_ended_mtx);
			return (0);
		}
		pthread_mutex_unlock(&p->resources->sim_ended_mtx);
		pthread_mutex_lock(&p->resources->forks_mtxs[right_fork_index]);
		if (p->resources->forks[right_fork_index] == AVAILABLE)
		{
			p->resources->forks[right_fork_index] = TAKEN;
			p->right_fork = HOLD;
			pthread_mutex_unlock(&p->resources->forks_mtxs[right_fork_index]);
			pthread_mutex_lock(&p->resources->sim_ended_mtx);
			if (p->resources->simulation_ended == false)
			{
				pthread_mutex_unlock(&p->resources->sim_ended_mtx);
				ft_print_fork_status(p, RIGHT_FORK);
			}
			else
				pthread_mutex_unlock(&p->resources->sim_ended_mtx);
			return(0);
		}
		pthread_mutex_unlock(&p->resources->forks_mtxs[right_fork_index]);
		//sched_yield();
	}
}

