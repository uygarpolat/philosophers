/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mutexes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:52:08 by upolat            #+#    #+#             */
/*   Updated: 2024/07/19 13:30:54 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_fork_mutexes(t_overseer *o)
{
	int	i;

	i = -1;
	while (++i < o->number_of_philos)
	{
		if (pthread_mutex_init(&o->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&o->forks[i]);
			return (0);
		}
	}
	return (1);
}

static int	init_write_mutexes(t_overseer *o)
{
	int	i;

	i = -1;
	while (++i < o->number_of_philos)
	{
		if (pthread_mutex_init(&o->write_mutex[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&o->write_mutex[i]);
			return (0);
		}
	}
	return (1);
}

static int	init_time_mutexes(t_overseer *o)
{
	int	i;

	i = -1;
	while (++i < o->number_of_philos)
	{
		if (pthread_mutex_init(&o->time_mutex[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&o->time_mutex[i]);
			return (0);
		}
	}
	return (1);
}

int	create_mutexes(t_overseer *o)
{
	if (!init_fork_mutexes(o))
		return (0);
	if (!init_write_mutexes(o))
	{
		destroy_fork_mutexes(o);
		return (0);
	}
	if (!init_time_mutexes(o))
	{
		destroy_fork_mutexes(o);
		destroy_write_mutexes(o);
		return (0);
	}
	if (pthread_mutex_init(&o->death_mutex, NULL) != 0)
	{
		destroy_fork_mutexes(o);
		destroy_write_mutexes(o);
		destroy_time_mutexes(o);
		return (0);
	}
	if (pthread_mutex_init(&o->print_mutex, NULL) != 0)
	{
		destroy_fork_mutexes(o);
		destroy_write_mutexes(o);
		destroy_time_mutexes(o);
		pthread_mutex_destroy(&o->death_mutex);
		return (0);
	}
	return (1);
}
