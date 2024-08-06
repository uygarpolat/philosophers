/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:30:22 by upolat            #+#    #+#             */
/*   Updated: 2024/08/07 00:19:56 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	write_state(char *str, t_philo *p)
{
	pthread_mutex_lock(p->death_mutex);
	if (!*p->death)
	{
		pthread_mutex_lock(p->print_mutex);
		printf("%zu %d %s\n", what_time_is_it()
			- p->sim_start_time, p->philo_num, str);
		pthread_mutex_unlock(p->print_mutex);
		pthread_mutex_unlock(p->death_mutex);
		return ;
	}
	pthread_mutex_unlock(p->death_mutex);
}

static int	threads_initial_check(t_philo *p)
{
	if (p->number_of_philos == 1)
	{
		pthread_mutex_lock(p->right_fork);
		write_state("has taken a fork", p);
		pthread_mutex_unlock(p->right_fork);
		return (0);
	}
	write_state("is thinking", p);
	if (p->philo_num % 2 == 0 || p->philo_num == p->number_of_philos)
	{
		if (p->time_to_eat > p->time_to_die)
			ft_usleep(p->time_to_die / 2, p);
		else
			ft_usleep(p->time_to_eat / 2, p); // <--- Only this was here originally, not the 3 lines above.
	}
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
		p->last_meal_time = what_time_is_it();
		pthread_mutex_unlock(p->time_mutex);
		if (p->time_to_eat > p->time_to_die)
			ft_usleep(p->time_to_die, p);
		else
			ft_usleep(p->time_to_eat, p); // <--- Only this was here originally, not the 3 lines above.
		pthread_mutex_unlock(p->right_fork);
		pthread_mutex_unlock(p->left_fork);
		write_state("is sleeping", p);
		pthread_mutex_lock(p->write_mutex);
		p->ate++;
		pthread_mutex_unlock(p->write_mutex);
		if (p->time_to_sleep > p->time_to_die)
			ft_usleep(p->time_to_die, p);
		else
			ft_usleep(p->time_to_sleep, p); // <--- Only this was here originally, not the 3 lines above.
		write_state("is thinking", p);
		pthread_mutex_lock(p->death_mutex);
	}
	pthread_mutex_unlock(p->death_mutex);
	return (NULL);
}
