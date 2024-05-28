/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:34:05 by aldokezer         #+#    #+#             */
/*   Updated: 2024/05/28 19:41:01 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

t_philosopher *ft_malloc_philosophers(int n_of_philos)
{
	t_philosopher *philosophers;

	philosophers = malloc(sizeof(t_philosopher) * (n_of_philos));
	if (!philosophers)
		return (NULL);
	else
		return (philosophers);
}

void ft_init_philosophres(t_simulation *simulation)
{
	t_philosopher *philosophers;
	int i;

	philosophers = ft_malloc_philosophers(simulation->n_of_threads);
	if (!philosophers)
		return ;
	simulation->philosophers = philosophers;
	i = 0;
	while (i < simulation->n_of_threads)
	{
		simulation->philosophers[i].id = i + 1;
		simulation->philosophers[i].resources = NULL;
		simulation->philosophers[i].eating_start = 0;
		simulation->philosophers[i].right_fork = 0;
		simulation->philosophers[i].left_fork = 0;
		i++;
	}
	return ;
}

// t_philosopher **ft_init_philosphers(int n)
// {
// 	t_philosopher **philosophers;
// 	int i;

// 	philosophers = (t_philosopher **) malloc(sizeof(t_philosopher *) * (n + 1));
// 	if (!philosophers)
// 		return (NULL);
// 	i = 0;
// 	while (i < n)
// 	{
// 		philosophers[i] = malloc(sizeof(t_philosopher));
// 		if (!philosophers[i])
// 			return (NULL);
// 		i++;
// 	}
// 	philosophers[i] = NULL;
// 	return (philosophers);
// }
