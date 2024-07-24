/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overseer_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:35:06 by upolat            #+#    #+#             */
/*   Updated: 2024/07/24 14:44:10 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	everyone_ate(t_overseer *o, int must_eat_temp)
{
	if (!o->must_eat_amount)
		return (0);
	sem_wait(o->write_sem);
	if (o->philos->ate < o->must_eat_amount)
	{
		sem_post(o->write_sem);
		return (0);
	}
	else if (must_eat_temp == o->must_eat_amount)
	{
		sem_post(o->write_sem);
		sem_post(o->terminate_sem);
		return (1);
	}
	sem_post(o->write_sem);
	return (0);
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
	int	terminate_count;
	int	must_eat_temp;

	must_eat_temp = o->must_eat_amount;
	terminate_count = o->number_of_philos;
	while (1)
	{
		if (is_there_death(o))
		{
			while (terminate_count--)
				sem_post(o->terminate_sem);
			return ;
		}
		if (everyone_ate(o, must_eat_temp))
			--must_eat_temp;
	}
}
