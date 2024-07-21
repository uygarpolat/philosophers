/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 00:31:07 by upolat            #+#    #+#             */
/*   Updated: 2024/07/21 20:21:37 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	handle_memory(t_philo **philo, t_overseer *o)
{
	*philo = malloc(sizeof(t_philo) * o->number_of_philos);
	if (*philo == NULL)
		return (0);
	o->forks = malloc(sizeof(pthread_mutex_t) * o->number_of_philos);
	if (o->forks == NULL)
	{
		free(*philo);
		return (0);
	}
	o->write_mutex = malloc(sizeof(pthread_mutex_t) * o->number_of_philos);
	if (o->write_mutex == NULL)
	{
		free(*philo);
		free(o->forks);
		return (0);
	}
	o->time_mutex = malloc(sizeof(pthread_mutex_t) * o->number_of_philos);
	if (o->time_mutex == NULL)
	{
		free(*philo);
		free(o->forks);
		free(o->write_mutex);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_overseer	overseer;

	if (argc < 5 || argc > 6 || !validity_check(argc, argv))
		return (write(2, "Usage error.\n", 13), 1);
	overseer.number_of_philos = ft_atoi(argv[1]);
	philo = NULL;
	if (!handle_memory(&philo, &overseer))
		return (write(2, "Failed to allocate memory.\n", 27), 1);
	overseer.philos = philo;
	if (!create_mutexes(&overseer))
	{
		free_malloc(philo, &overseer);
		write(2, "Failed to initialize mutex.\n", 28);
		return (1);
	}
	initialize_overseer(&overseer, argc, argv);
	initialize_table(philo, &overseer, argv);
	if (!create_threads(philo, &overseer))
		return (write(2, "Failed to create threads.\n", 26), 1);
	ft_overseer(&overseer);
	join_threads(philo, &overseer);
	free_and_destroy_mutexes(philo, &overseer);
	return (0);
}
