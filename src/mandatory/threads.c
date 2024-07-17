/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:54:41 by upolat            #+#    #+#             */
/*   Updated: 2024/07/18 00:54:59 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_philo *p, t_overseer *o)
{
	int				i;
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	i = 0;
	while (i < o->number_of_philos)
	{
		p[i].last_eating_time = start_time;
		p[i].last_eating_time2 = start_time;
		if (pthread_create(&p[i].thread, NULL,
				eat_sleep_think, (void *)&p[i]) != 0)
		{
			perror("pthread_create error");
			return ;
		}
		i++;
	}
}

void	join_threads(t_philo *p, t_overseer *o)
{
	int	i;

	i = -1;
	while (++i < o->number_of_philos)
		pthread_join(p[i].thread, NULL);
}
