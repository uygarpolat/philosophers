/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:54:41 by upolat            #+#    #+#             */
/*   Updated: 2024/08/07 13:59:57 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_philo *p, t_overseer *o)
{
	int		i;
	size_t	start_time;

	start_time = what_time_is_it();
	i = 0;
	while (i < o->number_of_philos)
	{
		p[i].sim_start_time = start_time;
		p[i].last_meal_time = start_time;
		if (pthread_create(&p[i].thread, NULL,
				eat_sleep_think, (void *)&p[i]) != 0)
		{
			pthread_mutex_lock(&o->death_mutex);
			o->death = 1;
			pthread_mutex_unlock(&o->death_mutex);
			while (--i >= 0)
				pthread_join(p[i].thread, NULL);
			free_and_destroy_mutexes(p, o);
			return (0);
		}
		i++;
	}
	return (1);
}

void	join_threads(t_philo *p, t_overseer *o)
{
	int	i;

	i = -1;
	while (++i < o->number_of_philos)
	{
		if (pthread_join(p[i].thread, NULL) != 0)
		{
			pthread_mutex_lock(&o->death_mutex);
			o->death = 1;
			pthread_mutex_unlock(&o->death_mutex);
			ft_putstr_fd("Failed to join thread.\n", 2);
		}
	}
}
