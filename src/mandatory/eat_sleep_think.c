/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:30:22 by upolat            #+#    #+#             */
/*   Updated: 2024/07/18 00:32:54 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	write_state(char *str, t_philo *p)
{
	pthread_mutex_lock(p->death_mutex);
	if (!*p->death)
		printf("%zu %d %s\n",
			get_relative_time(p->last_eating_time), p->philo_num, str);
	pthread_mutex_unlock(p->death_mutex);
}

static int	threads_initial_check(t_philo *p)
{
	if (p->number_of_philos == 1)
		return (0);
	pthread_mutex_lock(p->death_mutex);
	printf("%zu %d is thinking\n",
		get_relative_time(p->last_eating_time), p->philo_num);
	pthread_mutex_unlock(p->death_mutex);
	if (p->philo_num % 2 == 0 || p->philo_num == p->number_of_philos)
		ft_usleep(p->time_to_eat / 10, p->number_of_philos);
	pthread_mutex_lock(p->death_mutex);
	return (1);
}

static void	before_eating(t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	write_state("has taken a fork", p);
	pthread_mutex_lock(p->right_fork);
	write_state("has taken a fork", p);
	write_state("is eating", p);
}

void	*eat_sleep_think(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (!threads_initial_check(p))
		return (NULL);
	while (!*p->death)
	{
		pthread_mutex_unlock(p->death_mutex);
		before_eating(p);
		pthread_mutex_lock(p->time_mutex);
		gettimeofday(&p->last_eating_time2, NULL);
		pthread_mutex_unlock(p->time_mutex);
		ft_usleep(p->time_to_eat, p->number_of_philos);
		pthread_mutex_unlock(p->right_fork);
		pthread_mutex_unlock(p->left_fork);
		write_state("is sleeping", p);
		pthread_mutex_lock(p->write_mutex);
		p->ate++;
		pthread_mutex_unlock(p->write_mutex);
		ft_usleep(p->time_to_sleep, p->number_of_philos);
		write_state("is thinking", p);
		pthread_mutex_lock(p->death_mutex);
	}
	pthread_mutex_unlock(p->death_mutex);
	return (NULL);
}
