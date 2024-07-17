/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mutexes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:52:08 by upolat            #+#    #+#             */
/*   Updated: 2024/07/17 12:36:47 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
int	create_mutexes(t_overseer *o)
{
	int	i;

	i = 0;
	while (i < o->number_of_philos)
	{
		if (pthread_mutex_init(&o->forks[i], NULL) != 0)
		{
			perror("pthread_mutex_init error");
			return ;
		}
		i++;
	}
	if (pthread_mutex_init(&o->write_mutex, NULL) != 0)
	{
		perror("pthread_mutex_init error");
		return (0);
	}
	if (pthread_mutex_init(&o->death_mutex, NULL) != 0)
	{
		perror("pthread_mutex_init error");
		return (0);
	}
	if (pthread_mutex_init(&o->time_mutex, NULL) != 0)
	{
		perror("pthread_mutex_init error");
		return (0);
	}
	return (1);
}
*/

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
			write(2, "failed to initialize mutex\n", 28);
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
			write(2, "failed to initialize mutex\n", 28);
			return (0);
		}
	}
	return (1);
}



static void	destroy_fork_mutex(t_overseer *o)
{
	int	i;

	i = -1;
	while (++i < o->number_of_philos)
		pthread_mutex_destroy(&o->forks[i]);
}

int	create_mutexes(t_overseer *o)
{
	if (!init_fork_mutexes(o))
		return (0);
	if (!init_write_mutexes(o))
		return (0);  // THIS WAS ADDED LATER. MAKE SURE TO HANDLE ITS ERROR SITUATUIN IN "create_mutexes" FUNCTION.
	//if (pthread_mutex_init(&o->write_mutex, NULL) != 0)
	//{
	//	destroy_fork_mutex(o);
	//	write(2, "Failed to initialize mutex\n", 28);
	//	return (0);
	//}
	if (pthread_mutex_init(&o->death_mutex, NULL) != 0)
	{
		destroy_fork_mutex(o);
		//pthread_mutex_destroy(&o->write_mutex);
		write(2, "Failed to initialize mutex\n", 28);
		return (0);
	}
	if (pthread_mutex_init(&o->time_mutex, NULL) != 0)
	{
		destroy_fork_mutex(o);
		//pthread_mutex_destroy(&o->write_mutex);
		pthread_mutex_destroy(&o->death_mutex);
		write(2, "Failed to initialize mutex\n", 28);
		return (0);
	}
	return (1);
}

