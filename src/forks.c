/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:48:25 by aldokezer         #+#    #+#             */
/*   Updated: 2024/06/01 23:34:39 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

// MB has right_fork i + 0;
// ja mam i+1;

// MB has left_fork i + i;
// jam mam i+0;

/*
MB implementace
----------------
Kdyz p je sude id, pouzij i + 1; a left_fork()
Kdyz p je liche id, pouzij i + 0 a right_fork()
[F,F,F] - initial array of mtx; F = Free;
id: 0: left_fork() [F,X,F] - take left_fork=1
id: 1: right_fork() [F,F,F] - wait no change continue looping in right_fork()
id: 2: left_fork() [X,F,F] - take left_fork=1
[X,X,F]
-----------------------------------
Kdyz p ma oznaceny left_fork pouzij right_fork()
Kdyz p ma oznaceny right_fork pouzij left_fork()
[X,X,F]  - After odd/even selection
id: 0: right_fork() [X,X,2] - index 0 already taken by id 2, id 0 continues looping in right_fork()
id: 1: None [0,L,2] - id 1 is looping in right_fork() in the previous odd/even selection
id: 2: right_fork() [X,X,X] - index 2 is free id 2 takes it
id 2 will proceed to move to states
----------------------------------------------
*/
//***********************************//
// MB has right_fork i + 0;
// ja mam i+1;

// MB has left_fork i + i;
// jam mam i+0;

/*
OR implementace
----------------
Kdyz p je sude id, pouzij i + 1; a right_fork()
Kdyz p je liche id, pouzij i + 0 a left_fork()
[F,F,F] - initial array of mtx; F = Free;
id: 0: right_fork() [F,X,F] - take right_fork=1
id: 1: left_fork() [F,F,F] - wait no change continue looping in left_fork()
id: 2: right_fork() [X,F,F] - take right_fork=1
[X,X,F]
-----------------------------------
Kdyz p ma oznaceny left_fork pouzij right_fork()
Kdyz p ma oznaceny right_fork pouzij left_fork()
[X,X,F]  - After odd/even selection
id: 0: left_fork() [X,X,2] - index 0 already taken by id 2, id 0 continues looping in right_fork()
id: 1: None [0,L,2] - id 1 is looping in right_fork() in the previous odd/even selection
id: 2: left_fork() [X,X,X] - index 2 is free id 2 takes it
id 2 will proceed to move to states
----------------------------------------------
*/

inline static int	get_right_fork_index(t_philosopher *p)
{
	return ((p->id + 1) % p->resources->n_of_philosophers);
}

//O.R Implementation V1
void	ft_lock_forks(t_philosopher *p)
{
	if (p->id % 2)
		ft_lock_left_fork(p); // i + 0 liche id 1,3,5,7....
	else
		ft_lock_right_fork(p); // i + 1 sude id 0,2,4,6.....
	if (p->right_fork == HOLD)
		ft_lock_left_fork(p);
	else if (p->left_fork == HOLD)
		ft_lock_right_fork(p);
}

// O.R Implementation V2
// void	ft_lock_forks(t_philosopher *philosopher)
// {
// 	int	left_fork_index;
// 	int	right_fork_index;

// 	left_fork_index = philosopher->id;
// 	right_fork_index = get_right_fork_index(philosopher);
// 	if (left_fork_index < right_fork_index)
// 	{
// 		ft_lock_left_fork(philosopher);
// 		if (philosopher->left_fork == AVAILABLE)
// 			ft_lock_right_fork(philosopher);
// 	}
// 	else
// 	{
// 		ft_lock_right_fork(philosopher);
// 		if (philosopher->right_fork == AVAILABLE)
// 			ft_lock_left_fork(philosopher);
// 	}
// }

void	ft_release_forks(t_philosopher *p)
{
	int	left_index;
	int	right_index;

	left_index = p->id;
	right_index = get_right_fork_index(p);
	pthread_mutex_lock(&p->resources->forks_mtxs[left_index]);
	p->left_fork = RELEASE;
	p->resources->forks[left_index] = AVAILABLE;
	pthread_mutex_unlock(&p->resources->forks_mtxs[p->id]);
	pthread_mutex_lock(&p->resources->forks_mtxs[right_index]);
	p->right_fork = RELEASE;
	p->resources->forks[right_index] = AVAILABLE;
	pthread_mutex_unlock(&p->resources->forks_mtxs[right_index]);
}
