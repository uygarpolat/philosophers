/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:37:49 by upolat            #+#    #+#             */
/*   Updated: 2024/08/07 19:21:14 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	what_time_is_it(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(size_t milisecs, t_philo *p)
{
	size_t	start;
	size_t	i;

	i = 0;
	start = what_time_is_it();
	while (what_time_is_it() - start < milisecs)
	{
		if (i % 100 == 0)
		{
			pthread_mutex_lock(p->death_mutex);
			if (*p->death)
			{
				pthread_mutex_unlock(p->death_mutex);
				return ;
			}
			pthread_mutex_unlock(p->death_mutex);
		}
		i++;
		usleep(500);
	}
}
