/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 22:12:18 by aldokezer         #+#    #+#             */
/*   Updated: 2024/05/28 19:42:00 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philos.h"

// use static functions, variables and function pointers

//cc main.c -Wall -Wextra -Werror -o philos && ./philos

// states:

// eat - the state has condition to have two mutexes locked for a period of time
// sleep - state to keep the thread idle for certain period of time
// think - state in between sleep and eat without time period



int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	t_simulation simulation;
	simulation.n_of_threads = 5;
	ft_init_philosophres(&simulation);

	int i = 0;
	while (i < 5)
	{
		printf("Philosopher: %d\n", simulation.philosophers[i].id);
		i++;
	}
	return (0);
}
