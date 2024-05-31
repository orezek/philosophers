/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:45:57 by aldokezer         #+#    #+#             */
/*   Updated: 2024/05/31 20:45:46 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

void static ft_print_fork_status(t_philosopher *philospher, Side fork)
{
	long fork_time;

	fork_time = ft_get_current_time() - philospher->resources->sim_start_time;
	if (fork == RIGHT_FORK)
		printf("%-10ld%-6dhas taken a fork\n", fork_time, philospher->id + 1);
	else if (fork == LEFT_FORK)
		printf("%-10ld%-6dhas taken a fork\n", fork_time, philospher->id + 1);
}

static int get_right_fork_index(t_philosopher *p)
{
	return (p->id + 1) % p->resources->n_of_philosophers;
}


int	ft_lock_left_fork(t_philosopher *p)
{
	while (p->resources->simulation_ended == 0)
	{
		pthread_mutex_lock(&p->resources->forks_mtxs[p->id]);
		if (p->resources->forks[p->id] == AVAILABLE)
		{
			p->resources->forks[p->id] = TAKEN;
			p->left_fork = HOLD;
			pthread_mutex_unlock(&p->resources->forks_mtxs[p->id]);
			pthread_mutex_lock(&p->resources->print_console_mtx);
			if (p->resources->simulation_ended == false)
				ft_print_fork_status(p, LEFT_FORK);
			pthread_mutex_unlock(&p->resources->print_console_mtx);
			return (0);
		}
		pthread_mutex_unlock(&p->resources->forks_mtxs[p->id]);
	}
	return (0);
}

int	ft_lock_right_fork(t_philosopher *p)
{
	while (p->resources->simulation_ended == 0)
	{
		pthread_mutex_lock(&p->resources->forks_mtxs[get_right_fork_index(p)]); // 1 fork_mtx lock
		if (p->resources->forks[get_right_fork_index(p)] == AVAILABLE)
		{
			p->resources->forks[get_right_fork_index(p)] = TAKEN;
			p->right_fork = HOLD;
			pthread_mutex_unlock(&p->resources->forks_mtxs[get_right_fork_index(p)]); // 1 fork_mtx unlock
			pthread_mutex_lock(&p->resources->print_console_mtx); // 3 mtx lock
			if (p->resources->simulation_ended == false)
				ft_print_fork_status(p, RIGHT_FORK);
			pthread_mutex_unlock(&p->resources->print_console_mtx); // 3 mtx unlock
			return(0);
		}
		pthread_mutex_unlock(&p->resources->forks_mtxs[get_right_fork_index(p)]); // 1 fork_mtx unlock
	}
	return (0);
}

