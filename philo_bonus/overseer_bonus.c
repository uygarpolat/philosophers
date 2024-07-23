/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overseer_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:35:06 by upolat            #+#    #+#             */
/*   Updated: 2024/07/23 02:51:03 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	everyone_ate(t_overseer *o)
{
	//int	i;

	//i = 0;
	if (!o->must_eat_amount)
		return (0);
/*	while (i < o->number_of_philos)
	{
		sem_wait(&o->write_mutex[i]);
		if (o->philos[i].ate < o->must_eat_amount)
		{
			sem_post(&o->write_mutex[i]);
			return (0);
		}
		sem_post(&o->write_mutex[i]);
		i++;
	} */
	sem_wait(o->write_sem);
	if (o->philos->ate < o->must_eat_amount)
	{
		sem_post(o->write_sem);
		return (0);
	}
	sem_post(o->write_sem);
	sem_wait(o->death_sem);
	o->death = 1;
	sem_post(o->death_sem);
	return (1);
}

static void	announce_death(t_overseer *o, size_t t_meal, size_t t_sim)
{
	sem_post(o->write_sem);
	sem_wait(o->death_sem);
	o->death = 2;
	if (t_meal < t_sim)
		t_meal = t_sim;
	sem_wait(o->print_sem);
	printf("%zu %d died\n", t_meal, o->philos->philo_num);
	sem_post(o->print_sem);
	//sem_post(o->death_sem);
}

static int	is_there_death(t_overseer *o)
{
	size_t	t_meal;
	size_t	t_sim;

	t_sim = what_time_is_it() - o->philos->sim_start_time;
	sem_wait(o->time_sem);
	t_meal = what_time_is_it() - o->philos->last_meal_time;
	sem_post(o->time_sem);
	sem_wait(o->write_sem);
	if ((!o->philos->ate && t_sim > o->time_to_die)
		|| t_meal > o->time_to_die)
	{
		announce_death(o, t_meal, t_sim);
		return (1);
	}
	sem_post(o->write_sem);
	return (0);
}

void	ft_overseer(t_overseer *o)
{
	while (1)
	{
		if (is_there_death(o))
		{
			// sem_post(o->terminate_sem);
			return (2);
		}
		if (everyone_ate(o))
			return (1);
	}
}
