/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mutexes_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:52:08 by upolat            #+#    #+#             */
/*   Updated: 2024/07/23 00:02:47 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


int	initiate_sems(t_overseer *o)
{
	sem_unlink("fork_sem");
	o->fork_sem = sem_open("fork_sem", O_CREAT, 0644, o->number_of_philos);
	if (o->fork_sem == SEM_FAILED)
		return (1);
	sem_unlink("print_sem");
	o->print_sem = sem_open("print_sem", O_CREAT, 0644, 1);
	if (o->print_sem == SEM_FAILED)
		return (1);
	sem_unlink("death_sem");
	o->death_sem = sem_open("death_sem", O_CREAT, 0644, 1);
	if (o->death_sem == SEM_FAILED)
		return (1);
	sem_unlink("write_sem");
	o->write_sem = sem_open("write_sem", O_CREAT, 0644, 1);
	if (o->write_sem == SEM_FAILED)
		return (1);
	sem_unlink("terminate_sem");
	o->terminate_sem = sem_open("terminate_sem", O_CREAT, 0644, 0);
	if (o->terminate_sem == SEM_FAILED)
		return (1);
	sem_unlink("time_sem");
	o->time_sem = sem_open("time_sem", O_CREAT, 0644, 1);
	if (o->time_sem == SEM_FAILED)
		return (1);
	return (0);
}

/*
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

static void	batch_destroy_mutexes(t_overseer *o)
{
	destroy_fork_mutexes(o);
	destroy_write_mutexes(o);
	destroy_time_mutexes(o);
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
		batch_destroy_mutexes(o);
		return (0);
	}
	if (pthread_mutex_init(&o->print_mutex, NULL) != 0)
	{
		batch_destroy_mutexes(o);
		pthread_mutex_destroy(&o->death_mutex);
		return (0);
	}
	return (1);
}
*/
