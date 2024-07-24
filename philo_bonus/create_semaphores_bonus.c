/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_semaphores_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:52:08 by upolat            #+#    #+#             */
/*   Updated: 2024/07/23 23:51:36 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	open_death_sem(t_overseer *o)
{
	sem_unlink("death_sem");
	o->death_sem = sem_open("death_sem", O_CREAT, 0644, 1);
	if (o->death_sem == SEM_FAILED)
	{
		sem_close(o->fork_sem);
		sem_unlink("fork_sem");
		sem_close(o->print_sem);
		sem_unlink("print_sem");
		return (1);
	}
	return (0);
}

static int	open_write_sem(t_overseer *o)
{
	sem_unlink("write_sem");
	o->write_sem = sem_open("write_sem", O_CREAT, 0644, 1);
	if (o->write_sem == SEM_FAILED)
	{
		sem_close(o->fork_sem);
		sem_unlink("fork_sem");
		sem_close(o->print_sem);
		sem_unlink("print_sem");
		sem_close(o->death_sem);
		sem_unlink("death_sem");
		return (1);
	}
	return (0);
}

static int	open_terminate_sem(t_overseer *o)
{
	sem_unlink("terminate_sem");
	o->terminate_sem = sem_open("terminate_sem", O_CREAT, 0644, 0);
	if (o->terminate_sem == SEM_FAILED)
	{
		sem_close(o->fork_sem);
		sem_unlink("fork_sem");
		sem_close(o->print_sem);
		sem_unlink("print_sem");
		sem_close(o->death_sem);
		sem_unlink("death_sem");
		sem_close(o->write_sem);
		sem_unlink("write_sem");
		return (1);
	}
	return (0);
}

static int	open_time_sem(t_overseer *o)
{
	sem_unlink("time_sem");
	o->time_sem = sem_open("time_sem", O_CREAT, 0644, 1);
	if (o->time_sem == SEM_FAILED)
	{
		sem_close(o->fork_sem);
		sem_unlink("fork_sem");
		sem_close(o->print_sem);
		sem_unlink("print_sem");
		sem_close(o->death_sem);
		sem_unlink("death_sem");
		sem_close(o->write_sem);
		sem_unlink("write_sem");
		sem_close(o->terminate_sem);
		sem_unlink("terminate_sem");
		return (1);
	}
	return (0);
}

int	initiate_sems(t_overseer *o)
{
	sem_unlink("fork_sem");
	o->fork_sem = sem_open("fork_sem", O_CREAT, 0644, o->number_of_philos);
	if (o->fork_sem == SEM_FAILED)
		return (1);
	sem_unlink("print_sem");
	o->print_sem = sem_open("print_sem", O_CREAT, 0644, 1);
	if (o->print_sem == SEM_FAILED)
	{
		sem_close(o->fork_sem);
		sem_unlink("fork_sem");
		return (1);
	}
	if (open_death_sem(o))
		return (1);
	if (open_write_sem(o))
		return (1);
	if (open_terminate_sem(o))
		return (1);
	if (open_time_sem(o))
		return (1);
	return (0);
}
