/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:48:25 by aldokezer         #+#    #+#             */
/*   Updated: 2024/05/31 01:18:51 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"


static int ft_get_right_fork_index(t_philosopher *p)
{
	return (p->id + 1) % p->resources->n_of_philosophers;
}

static void ft_print_state(t_philosopher *p, char *message)
{
	long philosopher_eat_start;
	philosopher_eat_start = ft_get_sim_elapased_time(p->resources->sim_start_time);
	printf("%-10ld%-6d%s\n", philosopher_eat_start, p->id, message);
}

int	ft_lock_forks(t_philosopher *philosopher)
{
	if ((philosopher->id) % 2)
		ft_lock_right_fork(philosopher);
	else
		ft_lock_left_fork(philosopher);
	if (philosopher->left_fork == 1)
		ft_lock_right_fork(philosopher);
	else if (philosopher->right_fork == 1)
		ft_lock_left_fork(philosopher);
	return(0);
}



int ft_release_forks(t_philosopher *p)
{
	// release left fork
	pthread_mutex_lock(&p->resources->forks_mtxs[p->id]);
	p->left_fork = RELEASE;
	p->resources->forks[p->id] = AVAILABLE;
	pthread_mutex_unlock(&p->resources->forks_mtxs[p->id]);
	// release right fork
	pthread_mutex_lock(&p->resources->forks_mtxs[ft_get_right_fork_index(p)]);
	p->right_fork = RELEASE;
	p->resources->forks[ft_get_right_fork_index(p)] = AVAILABLE;
	pthread_mutex_unlock(&p->resources->forks_mtxs[ft_get_right_fork_index(p)]);
	// test
	pthread_mutex_lock(&p->resources->print_console_mtx);
	ft_print_state(p, "Forks released");
	pthread_mutex_unlock(&p->resources->print_console_mtx);
	return(0);
}
