/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:54:41 by upolat            #+#    #+#             */
/*   Updated: 2024/07/23 18:24:08 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	create_threads(t_philo *p, t_overseer *o)
{
	int		i;
	size_t	start_time;

	start_time = what_time_is_it();
	i = 0;
	while (i < o->number_of_philos)
	{
		o->pid[i] = fork();
		if (o->pid[i] == 0)
		{
			p->sim_start_time = start_time;
			p->last_meal_time = start_time;
			p->philo_num = i + 1;
			if (pthread_create(&p->thread, NULL,
					eat_sleep_think, (void *)p) != 0)
			{
				o->death = 1;
				//while (--i >= 0)
				//	pthread_join(p[i].thread, NULL);
				//free_and_destroy_mutexes(p, o);
				return (0);
			}
			ft_overseer(o);
			pthread_join(p->thread, NULL);
			exit(0);
		}
		i++;
	}
	return (1);
}
/*
void	join_threads(t_philo *p, t_overseer *o)
{
	int	i;

	i = -1;
	while (++i < o->number_of_philos)
		pthread_join(p[i].thread, NULL);
}
*/
