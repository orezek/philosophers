/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 22:13:16 by aldokezer         #+#    #+#             */
/*   Updated: 2024/05/28 19:41:21 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <pthread.h>

typedef struct s_philosopher t_philosopher;
typedef struct s_resource t_shared_resources;
typedef struct s_simulation t_simulation;

// thread struct aka philosopher
struct s_philosopher
{
	int id;
	bool left_fork;
	bool right_fork;
	int no_meals;
	long eating_start;
	t_shared_resources *resources;
};

// resource struct to hold shared resources for the simulation
struct s_resource
{
	char *test;
};

// main simulation struct to
struct s_simulation
{
	int	n_of_threads;
	t_philosopher *philosophers;
	t_shared_resources *resources;
};



// Function signatures

// Struct init
t_philosopher *ft_malloc_philosophers(int n_of_philos);
void ft_init_philosophres(t_simulation *simulation);
