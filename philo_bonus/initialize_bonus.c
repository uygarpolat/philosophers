/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:50:05 by upolat            #+#    #+#             */
/*   Updated: 2024/07/23 18:03:40 by upolat           ###   ########.fr       */
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
	p->number_of_philos = ft_atoi(argv[1]);
	p->time_to_eat = ft_atoi(argv[3]);
	p->time_to_sleep = ft_atoi(argv[4]);
	p->ate = 0;
	p->fork_sem = o->fork_sem;
	p->write_sem = o->write_sem;
	p->death_sem = &o->death_sem;
	p->print_sem = o->print_sem;
	p->time_sem = o->time_sem;
	p->terminate_sem = o->terminate_sem;
	p->death = &o->death;
}
