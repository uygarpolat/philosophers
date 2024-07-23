/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:54:41 by upolat            #+#    #+#             */
/*   Updated: 2024/07/23 02:51:10 by upolat           ###   ########.fr       */
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
			//if (i == 0)
			//{
			//	int sval;
			//	sem_getvalue(p->death_sem, &sval);
			//	printf("Semaphore value before entering threads: %d\n", sval);
			//}
			if (pthread_create(&p->thread, NULL,
					eat_sleep_think, (void *)p) != 0)
			{
				o->death = 1;
				//while (--i >= 0)
				//	pthread_join(p[i].thread, NULL);
				//free_and_destroy_mutexes(p, o);
				return (0);
			}
			if (ft_overseer(o) == 2)
				exit(1);
			pthread_join(p->thread, NULL);
			//sem_post(o->terminate_sem);
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
