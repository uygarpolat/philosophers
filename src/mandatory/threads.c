/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:54:41 by upolat            #+#    #+#             */
/*   Updated: 2024/07/19 19:35:32 by upolat           ###   ########.fr       */
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
		p[i].last_eating_time = start_time;
		p[i].last_eating_time2 = start_time;
		if (pthread_create(&p[i].thread, NULL,
				eat_sleep_think, (void *)&p[i]) != 0)
		{
			o->death = 1;
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
		pthread_join(p[i].thread, NULL);
}
