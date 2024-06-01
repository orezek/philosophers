/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 22:13:16 by aldokezer         #+#    #+#             */
/*   Updated: 2024/06/02 01:40:28 by aldokezer        ###   ########.fr       */
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

#define IGNORE -1

typedef struct s_philosopher t_philosopher;
typedef struct s_shared_resources t_shared_resources;
typedef struct s_simulation t_simulation;

typedef  enum
{
	TAKEN = 0,
	AVAILABLE = 1
} Status;

typedef  enum
{
	LEFT_FORK = 0,
	RIGHT_FORK = 1
} Side;

typedef  enum
{
	RELEASE = 0,
	HOLD = 1
} State;

typedef enum
{
	MILLISECOND,
	MICROSECOND,
	SECONDS
} Time_code;

// thread struct aka philosopher
struct s_philosopher
{
	int id;
	bool left_fork;
	bool right_fork;
	int no_meals;
	long eating_start;
	pthread_mutex_t	no_meals_mtx;
	pthread_mutex_t	eating_start_mtx;
	pthread_t thread;
	t_shared_resources *resources;
	t_simulation *simulation;
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
	pthread_mutex_t	print_console_mtx;
	pthread_mutex_t	*forks_mtxs;
};

// main simulation struct
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
void	ft_init_philosophres(t_simulation *simulation);

// Shared resources init functions
void	ft_init_resources(t_simulation *simulation);

// Mutex init functions
void	ft_init_mutexes(t_simulation *simulation);

// Cleaning functions
void	ft_clear_sim_memory(t_simulation *simulation);
void	ft_clear_mutexes(t_simulation *simulation);

// Utility functions

// Time handling functions
long int	ft_get_current_time(void);
long		ft_get_sim_elapased_time(long sim_start_time);
void		ft_sleep(long period);
void		ft_precise_sleep(long period, t_philosopher *p);
long	gettime(int time_code);

// Fork handling functions
void	ft_lock_forks(t_philosopher *philosopher);
void	ft_release_forks(t_philosopher *philosopher);

// Fork utils
int	ft_lock_left_fork(t_philosopher *p);
int	ft_lock_right_fork(t_philosopher *p);

// For handling philosopher states
void ft_eat_state(t_philosopher *philosopher);
void ft_sleep_state(t_philosopher *philosopher);
void ft_think_state(t_philosopher *philosopher);

// Thread execution functions
void	*ft_sim_execution(void *philosopher);

// Control thread for simulation status
void *ft_simulation_control(void *simulation);
