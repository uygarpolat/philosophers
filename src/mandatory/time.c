/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:37:49 by upolat            #+#    #+#             */
/*   Updated: 2024/07/19 14:17:48 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	what_time_is_it_us(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(size_t milisecs, int number_of_philos)
{
	size_t	start;
	size_t	nanosecs;
	
	nanosecs = milisecs;
	start = what_time_is_it_us();
	while ((what_time_is_it_us() - start) < nanosecs)
		usleep(number_of_philos * 2);
}

size_t	get_relative_time(struct timeval start_time)
{
	struct timeval	current_time;
	long	seconds;
	long	useconds;

	gettimeofday(&current_time, NULL);
	seconds = current_time.tv_sec - start_time.tv_sec;
	useconds = current_time.tv_usec - start_time.tv_usec;
	if (useconds < 0)
	{
		seconds -= 1;
		useconds += 1000000;
	}
	return ((seconds * 1000) + (useconds / 1000));
}
