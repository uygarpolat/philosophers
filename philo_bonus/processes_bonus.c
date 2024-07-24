/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:54:41 by upolat            #+#    #+#             */
/*   Updated: 2024/07/24 13:07:16 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	create_thread(t_philo *p, t_overseer *o, int i, size_t start_time)
{
	p->sim_start_time = start_time;
	p->last_meal_time = start_time;
	p->philo_num = i + 1;
	if (pthread_create(&p->thread, NULL,
			eat_sleep_think, (void *)p) != 0)
	{
		write(2, "Failed to create thread.\n", 25);
		while (o->number_of_philos--)
			sem_post(o->terminate_sem);
		exit (1);
	}
	ft_overseer(o);
	pthread_join(p->thread, NULL);
	exit(0);
}

int	create_processes(t_philo *p, t_overseer *o)
{
	int		i;
	size_t	start_time;

	start_time = what_time_is_it();
	i = 0;
	while (i < o->number_of_philos)
	{
		o->pid[i] = fork();
		if (o->pid[i] == -1)
		{
			while (--i >= 0)
				kill(o->pid[i], SIGKILL);
			free(o->pid);
			write(2, "Error running fork.\n", 20);
			exit (1);
		}
		else if (o->pid[i] == 0)
			create_thread(p, o, i, start_time);
		i++;
	}
	return (0);
}
