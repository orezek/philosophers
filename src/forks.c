/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:48:25 by aldokezer         #+#    #+#             */
/*   Updated: 2024/05/29 21:44:40 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

int	ft_lock_forks(t_philosopher *philosopher)
{
	(void)philosopher;
	printf("Phil: %d Locks\n", philosopher->id);
	return(0);
}

int ft_release_forks(t_philosopher *philosopher)
{
	(void)philosopher;
	printf("Phil: %d Unlocks\n", philosopher->id);
	return(0);
}
