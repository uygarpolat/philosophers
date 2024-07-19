/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overseer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:35:06 by upolat            #+#    #+#             */
/*   Updated: 2024/07/19 17:42:29 by upolat           ###   ########.fr       */
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

static int	is_there_death(t_overseer *o)
{
	int		i;
	size_t	time_since_start_of_meal;

	i = -1;
	while (++i < o->number_of_philos)
	{
		pthread_mutex_lock(&o->time_mutex[i]);
		time_since_start_of_meal = what_time_is_it()
			- o->philos[i].last_eating_time2;
		pthread_mutex_unlock(&o->time_mutex[i]);
		if (time_since_start_of_meal >= o->time_to_die)
		{
			pthread_mutex_lock(&o->death_mutex);
			o->death = 2;
			pthread_mutex_unlock(&o->death_mutex);
			pthread_mutex_lock(&o->print_mutex);
			printf("%zu %d died\n", what_time_is_it()
				- o->philos[i].last_eating_time, i + 1);
			pthread_mutex_unlock(&o->print_mutex);
			return (1);
		}
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
