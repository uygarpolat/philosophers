/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overseer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:35:06 by upolat            #+#    #+#             */
/*   Updated: 2024/07/21 03:07:32 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	everyone_ate(t_overseer *o)
{
	int	i;

	i = 0;
	if (!o->must_eat_amount)
		return (0);
	while (i < o->number_of_philos)
	{
		pthread_mutex_lock(&o->write_mutex[i]);
		if (o->philos[i].ate < o->must_eat_amount)
		{
			pthread_mutex_unlock(&o->write_mutex[i]);
			return (0);
		}
		pthread_mutex_unlock(&o->write_mutex[i]);
		i++;
	}
	pthread_mutex_lock(&o->death_mutex);
	o->death = 1;
	pthread_mutex_unlock(&o->death_mutex);
	return (1);
}

static void	announce_death(t_overseer *o, size_t t_meal, size_t t_sim, int i)
{
	pthread_mutex_unlock(&o->write_mutex[i]);
	pthread_mutex_lock(&o->death_mutex);
	o->death = 2;
	if (t_meal < t_sim)
		t_meal = t_sim;
	pthread_mutex_lock(&o->print_mutex);
	printf("%zu %d died\n", t_meal, i + 1);
	pthread_mutex_unlock(&o->print_mutex);
	pthread_mutex_unlock(&o->death_mutex);
}

static int	is_there_death(t_overseer *o)
{
	int		i;
	size_t	t_meal;
	size_t	t_sim;

	i = -1;
	while (++i < o->number_of_philos)
	{
		t_sim = what_time_is_it() - o->philos[i].sim_start_time;
		pthread_mutex_lock(&o->time_mutex[i]);
		t_meal = what_time_is_it() - o->philos[i].last_meal_time;
		pthread_mutex_unlock(&o->time_mutex[i]);
		pthread_mutex_lock(&o->write_mutex[i]);
		if ((!o->philos[i].ate && t_sim > o->time_to_die)
			|| t_meal > o->time_to_die)
		{
			announce_death(o, t_meal, t_sim, i);
			return (1);
		}
		pthread_mutex_unlock(&o->write_mutex[i]);
	}
	return (0);
}

void	ft_overseer(t_overseer *o)
{
	while (1)
	{
		if (is_there_death(o))
			return ;
		if (everyone_ate(o))
			return ;
	}
}
