/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:50:05 by upolat            #+#    #+#             */
/*   Updated: 2024/07/21 20:20:34 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	initialize_overseer(t_overseer *o, int argc, char **argv)
{
	o->death = 0;
	o->time_to_die = ft_atoi(argv[2]);
	if (argc == 6)
		o->must_eat_amount = ft_atoi(argv[5]);
	else
		o->must_eat_amount = 0;
}

void	initialize_table(t_philo *p, t_overseer *o, char **argv)
{
	int	i;

	i = 0;
	while (i < o->number_of_philos)
	{
		p[i].philo_num = i + 1;
		p[i].number_of_philos = ft_atoi(argv[1]);
		p[i].time_to_eat = ft_atoi(argv[3]);
		p[i].time_to_sleep = ft_atoi(argv[4]);
		p[i].ate = 0;
		p[i].left_fork = &o->forks[i];
		p[i].right_fork = &o->forks[(i + 1) % o->number_of_philos];
		p[i].write_mutex = &o->write_mutex[i];
		p[i].death_mutex = &o->death_mutex;
		p[i].print_mutex = &o->print_mutex;
		p[i].time_mutex = &o->time_mutex[i];
		p[i].death = &o->death;
		i++;
	}
}
