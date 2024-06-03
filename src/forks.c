/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:48:25 by aldokezer         #+#    #+#             */
/*   Updated: 2024/06/03 23:24:22 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

inline static int	get_right_fork_index(t_philosopher *p)
{
	return ((p->id + 1) % p->resources->n_of_philosophers);
}

void	ft_lock_forks(t_philosopher *p)
{
	if (p->id % 2)
		ft_lock_left_fork(p);
	else
		ft_lock_right_fork(p);
	if (p->right_fork == HOLD)
		ft_lock_left_fork(p);
	else if (p->left_fork == HOLD)
		ft_lock_right_fork(p);
}

void	ft_release_forks(t_philosopher *p)
{
	int	left_index;
	int	right_index;

	left_index = p->id;
	right_index = get_right_fork_index(p);
	pthread_mutex_lock(&p->resources->forks_mtxs[left_index]);
	p->left_fork = RELEASE;
	p->resources->forks[left_index] = AVAILABLE;
	pthread_mutex_unlock(&p->resources->forks_mtxs[left_index]);
	pthread_mutex_lock(&p->resources->forks_mtxs[right_index]);
	p->right_fork = RELEASE;
	p->resources->forks[right_index] = AVAILABLE;
	pthread_mutex_unlock(&p->resources->forks_mtxs[right_index]);
}
