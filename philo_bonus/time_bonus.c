/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:37:49 by upolat            #+#    #+#             */
/*   Updated: 2024/07/22 18:38:16 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	what_time_is_it(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "Failed to retrieve time.\n", 25);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(size_t milisecs, t_philo *p)
{
	size_t	start;

	sem_wait(p->death_sem);
	if (*p->death)
	{
		sem_post(p->death_sem);
		return ;
	}
	sem_post(p->death_sem);
	start = what_time_is_it();
	while ((what_time_is_it() - start) < milisecs)
		usleep(500);
}
