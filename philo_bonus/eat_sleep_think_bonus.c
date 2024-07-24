/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:30:22 by upolat            #+#    #+#             */
/*   Updated: 2024/07/25 00:34:16 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	write_state(char *str, t_philo *p)
{
	sem_wait(*p->death_sem);
	if (!*p->death)
	{
		sem_wait(p->print_sem);
		printf("%zu %d %s\n", what_time_is_it()
			- p->sim_start_time, p->philo_num, str);
		sem_post(p->print_sem);
		sem_post(*p->death_sem);
		return ;
	}
	sem_post(*p->death_sem);
}

static int	threads_initial_check(t_philo *p)
{
	if (p->number_of_philos == 1)
	{
		sem_wait(p->fork_sem);
		write_state("has taken a fork", p);
		sem_post(p->fork_sem);
		return (0);
	}
	write_state("is thinking", p);
	if (p->philo_num > p->number_of_philos / 2)
		ft_usleep(p->time_to_sleep / 2, p);
	sem_wait(*p->death_sem);
	return (1);
}

static void	before_eating(t_philo *p)
{
	sem_wait(p->fork_sem);
	write_state("has taken a fork", p);
	sem_wait(p->fork_sem);
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
		sem_post(*p->death_sem);
		before_eating(p);
		sem_wait(p->time_sem);
		p->last_meal_time = what_time_is_it();
		sem_post(p->time_sem);
		ft_usleep(p->time_to_eat, p);
		sem_post(p->fork_sem);
		sem_post(p->fork_sem);
		write_state("is sleeping", p);
		sem_wait(p->write_sem);
		p->ate++;
		sem_post(p->write_sem);
		ft_usleep(p->time_to_sleep, p);
		write_state("is thinking", p);
		sem_wait(*p->death_sem);
	}
	sem_post(*p->death_sem);
	return (NULL);
}
