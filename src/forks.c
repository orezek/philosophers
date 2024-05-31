/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:48:25 by aldokezer         #+#    #+#             */
/*   Updated: 2024/05/31 17:04:33 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"


static int get_right_fork_index(t_philosopher *p)
{
	return (p->id + 1) % p->resources->n_of_philosophers;
}

int ft_lock_forks(t_philosopher *philosopher)
{
	int left_fork_index = philosopher->id;
	int right_fork_index = get_right_fork_index(philosopher);

	if (left_fork_index < right_fork_index)
	{
		ft_lock_left_fork(philosopher);
		if (philosopher->left_fork == AVAILABLE)
			ft_lock_right_fork(philosopher);
	}
	else
	{
		ft_lock_right_fork(philosopher);
		if (philosopher->right_fork == AVAILABLE)
			ft_lock_left_fork(philosopher);
	}
	return 0;
}

int ft_release_forks(t_philosopher *p)
{
	pthread_mutex_lock(&p->resources->forks_mtxs[p->id]);
	p->left_fork = RELEASE;
	p->resources->forks[p->id] = AVAILABLE;
	pthread_mutex_unlock(&p->resources->forks_mtxs[p->id]);
	pthread_mutex_lock(&p->resources->forks_mtxs[get_right_fork_index(p)]);
	p->right_fork = RELEASE;
	p->resources->forks[get_right_fork_index(p)] = AVAILABLE;
	pthread_mutex_unlock(&p->resources->forks_mtxs[get_right_fork_index(p)]);
	return(0);
}
