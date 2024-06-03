/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 20:41:45 by aldokezer         #+#    #+#             */
/*   Updated: 2024/06/03 23:44:34 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

int	ft_int_atoi(const char *str)
{
	int		i;
	long	sign;
	long	number;

	i = 0;
	sign = 1;
	number = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	else if (!(str[i] >= '0' && str[i] <= '9'))
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
		number = number * 10 + str[i++] - '0';
	number = number * sign;
	if (number <= INT_MAX && number >= 0)
		return ((long int) number);
	return (-1);
}

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		write(fd, s++, 1);
	}
}

int	ft_parse_input(t_simulation *s, int argc, char **argv)
{
	if (argc > 1 && argc < 6)
	{
		s->resources->n_of_philosophers = ft_int_atoi(argv[1]);
		s->resources->time_to_die = ft_int_atoi(argv[2]);
		s->resources->time_to_eat = ft_int_atoi(argv[3]);
		s->resources->time_sleep = ft_int_atoi(argv[4]);
	}
	if (argc == 6)
		s->resources->no_of_iterations = ft_int_atoi(argv[5]);
	return (0);
}
