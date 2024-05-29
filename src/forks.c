/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:48:25 by aldokezer         #+#    #+#             */
/*   Updated: 2024/05/29 21:34:43 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

int	ft_lock_forks(t_philosopher *philosophers)
{
	(void)philosophers;
	printf("Lock forks\n");
	return(0);
}

int ft_release_forks(t_philosopher *philosophers)
{
	(void)philosophers;
	printf("Unlock forks\n");
	return(0);
}
