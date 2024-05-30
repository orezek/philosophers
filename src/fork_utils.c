/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:45:57 by aldokezer         #+#    #+#             */
/*   Updated: 2024/05/31 01:51:49 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

void static ft_print_fork_status(t_philosopher *philospher, Side fork)
{
	long fork_time;

	fork_time = ft_get_current_time() - philospher->resources->sim_start_time;
	if (fork)
		printf("%-10ld%-6dhas taken a right fork\n", fork_time, philospher->id);
	else
		printf("%-10ld%-6dhas taken a left fork\n", fork_time, philospher->id);
}

static int ft_get_right_fork_index(t_philosopher *p)
{
	return (p->id + 1) % p->resources->n_of_philosophers;
}


int	ft_lock_left_fork(t_philosopher *p)
{
	int loop_control;
// 1,3 right and mark left
// 1 right marked mtx2
// left
// 1 fork_mtx index 1
// fork_flag index 1
	loop_control = 1;
	pthread_mutex_lock(&p->resources->print_console_mtx);
	while (loop_control == 1 && p->resources->simulation_ended == 0)
	{
		pthread_mutex_unlock(&p->resources->print_console_mtx);
		pthread_mutex_lock(&p->resources->forks_mtxs[p->id]);
		if (p->resources->forks[p->id] == AVAILABLE)
		{
			p->resources->forks[p->id] = TAKEN;
			p->left_fork = HOLD;
			// print status
			pthread_mutex_lock(&p->resources->print_console_mtx);
			if (p->resources->simulation_ended == false)
				ft_print_fork_status(p, LEFT_FORK);
			pthread_mutex_unlock(&p->resources->print_console_mtx);
			//----end status
			pthread_mutex_unlock(&p->resources->forks_mtxs[p->id]);
			loop_control = 0;
		}
		else
		{
			pthread_mutex_unlock(&p->resources->forks_mtxs[p->id]);
		}
		pthread_mutex_lock(&p->resources->print_console_mtx);
	}
	pthread_mutex_unlock(&p->resources->print_console_mtx);
	return (0);
}

int	ft_lock_right_fork(t_philosopher *p)
{
	int loop_control;

	loop_control = 1;
	pthread_mutex_lock(&p->resources->print_console_mtx); // 2 mtx lock
	while (loop_control == 1 && p->resources->simulation_ended == 0)
	{
		pthread_mutex_unlock(&p->resources->print_console_mtx); // 2 mtx unlock
		pthread_mutex_lock(&p->resources->forks_mtxs[ft_get_right_fork_index(p)]); // 1 fork_mtx lock
		if (p->resources->forks[ft_get_right_fork_index(p)] == AVAILABLE)
		{
			p->resources->forks[ft_get_right_fork_index(p)] = TAKEN;
			p->right_fork = HOLD;
			pthread_mutex_lock(&p->resources->print_console_mtx); // 3 mtx lock
			if (p->resources->simulation_ended == false)
				ft_print_fork_status(p, RIGHT_FORK);
			pthread_mutex_unlock(&p->resources->print_console_mtx); // 3 mtx unlock
			pthread_mutex_unlock(&p->resources->forks_mtxs[ft_get_right_fork_index(p)]); // 1 fork_mtx unlock
			loop_control = 0;
		}
		else
		{
			pthread_mutex_unlock(&p->resources->forks_mtxs[ft_get_right_fork_index(p)]); // 1 fork_mtx unlock
		}
		pthread_mutex_lock(&p->resources->print_console_mtx); // 4 mtx lock
	}
	pthread_mutex_unlock(&p->resources->print_console_mtx); // 4 mtx unlock
	return (0);
}

