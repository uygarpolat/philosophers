/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:23:55 by upolat            #+#    #+#             */
/*   Updated: 2024/07/24 20:48:14 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_fork_mutexes(t_overseer *o)
{
	int	i;

	i = -1;
	while (++i < o->number_of_philos)
		pthread_mutex_destroy(&o->forks[i]);
}

void	destroy_write_mutexes(t_overseer *o)
{
	int	i;

	i = -1;
	while (++i < o->number_of_philos)
		pthread_mutex_destroy(&o->write_mutex[i]);
}

void	destroy_time_mutexes(t_overseer *o)
{
	int	i;

	i = -1;
	while (++i < o->number_of_philos)
		pthread_mutex_destroy(&o->time_mutex[i]);
}

void	free_malloc(t_philo *philo, t_overseer *overseer)
{
	if (philo)
		free(philo);
	philo = NULL;
	if (overseer->forks)
		free(overseer->forks);
	overseer->forks = NULL;
	if (overseer->write_mutex)
		free(overseer->write_mutex);
	overseer->write_mutex = NULL;
	if (overseer->time_mutex)
		free(overseer->time_mutex);
	overseer->time_mutex = NULL;
}

void	free_and_destroy_mutexes(t_philo *philo, t_overseer *overseer)
{
	destroy_fork_mutexes(overseer);
	destroy_write_mutexes(overseer);
	destroy_time_mutexes(overseer);
	pthread_mutex_destroy(&overseer->death_mutex);
	pthread_mutex_destroy(&overseer->print_mutex);
	free_malloc(philo, overseer);
}
