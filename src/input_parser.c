/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 20:39:41 by aldokezer         #+#    #+#             */
/*   Updated: 2024/06/03 22:31:06 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philos.h"

int	args_error(void)
{
	ft_putstr_fd("Error: "
		"Input must be a non-negative integer, "
		"with correct number of parameters.\n", 2);
	printf("Correct input: ./philo n_of_p time_to_die "
		"time_eat time_sleep "
		"[num_of_times_must_p_eat]\n");
	return (1);
}

int	zero_philo_error(void)
{
	ft_putstr_fd("Error: At least one philosopher needed.", 2);
	return (1);
}

int	check_args(int argc, char **argv)
{
	if (argc > 0 && argc < 5)
		return (args_error());
	if (argc == 5 || argc == 6)
	{
		if (ft_int_atoi(argv[1]) < 0)
			return (args_error());
		if (ft_int_atoi(argv[1]) == 0)
			return (zero_philo_error());
		if (ft_int_atoi(argv[2]) < 0 || ft_int_atoi(argv[3]) < 0 || ft_int_atoi(argv[4]) < 0)
			return (args_error());
	}
	if (argc == 6)
	{
		if (ft_int_atoi(argv[5]) <= 0)
			return (args_error());
	}
	if (argc > 6)
		return (args_error());
	return (0);
}
