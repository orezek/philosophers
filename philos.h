/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 22:13:16 by aldokezer         #+#    #+#             */
/*   Updated: 2024/05/29 12:13:09 by aldokezer        ###   ########.fr       */
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
typedef struct s_shared_resources t_shared_resources;
typedef struct s_simulation t_simulation;

typedef  enum
{
	TAKEN = 0,
	AVAILABLE = 1
} Status;

// thread struct aka philosopher
struct s_philosopher
{
	int id;
	bool left_fork;
	bool right_fork;
	int no_meals;
	long eating_start;
	pthread_t thread;
	t_shared_resources *resources;
};

// resource struct to hold shared resources for the simulation
struct s_shared_resources
{
	int		*forks;
	bool	simulation_ended;
	long	sim_start_time;
	int		n_of_philosophers;
	long	time_to_die;
	long	time_to_eat;
	long	time_sleep;
	int		no_of_iterations;
};

// main simulation struct to
struct s_simulation
{
	pthread_t control_thread;
	t_philosopher *philosophers;
	t_shared_resources *resources;
};



// Function signatures

// Simulation init functions
void ft_init_simulation(t_simulation *simulation, char *argv[]);
t_simulation *ft_malloc_simulation(void);

// Philosphers init functions
void ft_init_philosophres(t_simulation *simulation);

// Shared resources init functions
void ft_init_resources(t_simulation *simulation);

// Cleaning functions
void ft_clear_sim_memory(t_simulation *simulation);

// Utility functions
int	philosophers(t_simulation *simulation);

// Time handling functions
long int	ft_get_current_time(void);
long		ft_get_sim_elapased_time(long sim_start_time);
void		ft_sleep(long period);

// Fork handling functions
int	ft_lock_forks(t_simulation *simulation);
int ft_release_forks(t_simulation *t_simulation);

// For handling philosopher states
int ft_eat_state(t_simulation *simulation);
int ft_sleep_state(t_simulation *simulation);
int ft_think_state(t_simulation *simulation);

// Thread execution functions
void	*ft_sim_execution(void *simulation);
