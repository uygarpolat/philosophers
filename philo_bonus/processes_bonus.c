/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:54:41 by upolat            #+#    #+#             */
/*   Updated: 2024/07/24 14:32:03 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	create_thread(t_philo *p, t_overseer *o, int i, size_t start_time)
{
	int	number_of_philos;

	number_of_philos = o->number_of_philos;
	p->sim_start_time = start_time;
	p->last_meal_time = start_time;
	p->philo_num = i + 1;
	if (pthread_create(&p->thread, NULL,
			eat_sleep_think, (void *)p) != 0)
	{
		ft_putstr_fd("Failed to create thread.\n", 2);
		while (number_of_philos--)
			sem_post(o->terminate_sem);
		exit (1);
	}
	ft_overseer(o);
	pthread_join(p->thread, NULL);
	exit(0);
}

void	create_processes(t_philo *p, t_overseer *o)
{
	int		i;
	int		number_of_philos;
	size_t	start_time;

	start_time = what_time_is_it();
	i = 0;
	while (i < o->number_of_philos)
	{
		o->pid[i] = fork();
		if (o->pid[i] == -1)
		{
			number_of_philos = o->number_of_philos;
			ft_putstr_fd("Failed to run fork.\n", 2);
			while (number_of_philos--)
				sem_post(o->terminate_sem);
			return ;
		}
		else if (o->pid[i] == 0)
			create_thread(p, o, i, start_time);
		i++;
	}
	return ;
}
