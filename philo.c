/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 00:31:07 by upolat            #+#    #+#             */
/*   Updated: 2024/06/28 03:38:04 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>
#include <unistd.h>
#include "philo.h"

void	*eat_sleep_think(void *arg);

static int	ft_isspace(const char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int			sign;
	long long	nbr;

	sign = 1;
	nbr = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
	{
		sign = -sign;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (sign == 1 && (nbr > (INT_MAX - (*str - '0')) / 10))
			return (-1);
		else if (sign == -1 && (-nbr < (INT_MIN + (*str - '0')) / 10))
			return (0);
		nbr = nbr * 10 + *str - '0';
		str++;
	}
	return (sign * nbr);
}
/*
long	get_relative_time(long last_eating_time)
{
	struct timeval	current_time;
	long			seconds;
	long			useconds;

	gettimeofday(&current_time, NULL);
	seconds = current_time.tv_sec - start_time.tv_sec;
	useconds = current_time.tv_usec - start_time.tv_usec;
	return ((seconds * 1000) + (useconds / 1000));
}
*/
long	get_relative_time(struct timeval start_time)
{
	struct timeval	current_time;
	long			seconds;
	long			useconds;

	gettimeofday(&current_time, NULL);
	seconds = current_time.tv_sec - start_time.tv_sec;
	useconds = current_time.tv_usec - start_time.tv_usec;
	return ((seconds * 1000) + (useconds / 1000));
}

void	initialize_overseer(t_philo *p, t_overseer *o, int argc, char **argv)
{
	(void)p;
	(void)o;
	(void)argc;
	(void)argv;
	o->death = 0;
}

void	initialize_table(t_philo *p, t_overseer *o, int argc, char **argv)
{
	int	i;
	
	i = 0;
	while (i < o->number_of_philos)
	{
		p[i].number_of_philos = ft_atoi(argv[1]);
		p[i].number_of_forks = ft_atoi(argv[1]);
		p[i].philo_num = i + 1;
		p[i].time_to_die = ft_atoi(argv[2]);
		p[i].time_to_eat = ft_atoi(argv[3]);
		p[i].time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			p[i].must_eat_amount = ft_atoi(argv[5]);
		else
			p[i].must_eat_amount = INT_MAX;
		p[i].left_fork = &o->forks[i];
		p[i].right_fork = &o->forks[(i + 1) % o->number_of_philos];
		p[i].write_mutex = &o->write_mutex;
		p[i].death_mutex = &o->death_mutex;
		p[i].death = &o->death;
		gettimeofday(&p[i].last_eating_time, NULL);
		i++;
	}
}

void	create_mutexes(t_overseer *o)
{
	int	i;

	i = 0;
	while (i < o->number_of_philos)
	{
		if (pthread_mutex_init(&o->forks[i], NULL) != 0)
		{
			perror("pthread_mutex_init error");
			return ;
		}
		i++;
	}
	if (pthread_mutex_init(&o->write_mutex, NULL) != 0)
	{
		perror("pthread_mutex_init error");
		return ;
	}
	if (pthread_mutex_init(&o->death_mutex, NULL) != 0)
	{
		perror("pthread_mutex_init error");
		return ;
	}
}

void	create_threads(t_philo *p, t_overseer *o)
{
	int	i;

	i = 0;
	while (i < o->number_of_philos)
	{
		if (pthread_create(&p[i].thread, NULL, eat_sleep_think, (void *)&p[i]) != 0)
		{
			perror("pthread_create error");
			return ;
		}
		i++;
	}
}

void	join_threads(t_philo *p, t_overseer *o)
{
	int	i;

	i = 0;
	while (i < o->number_of_philos)
	{
		if (pthread_join(p[i].thread, NULL) != 0)
		{
			perror("pthread_join error");
			return ;
		}
		i++;
	}
}

void	destroy_mutexes(t_overseer *o)
{
	int	i;

	i = 0;
	while (i < o->number_of_philos)
	{
		if (pthread_mutex_destroy(&o->forks[i]) != 0)
		{
			perror("pthread_mutex_destroy error");
			return ;
		}
		i++;
	}
	if (pthread_mutex_destroy(&o->write_mutex) != 0)
	{
		perror("pthread_mutex_destroy error");
		return ;
	}
	if (pthread_mutex_destroy(&o->death_mutex) != 0)
	{
		perror("pthread_mutex_destroy error");
		return ;
	}
	// Is checking if it is equal to zero how you handle errors in destroying?
	// It was copy/pasted from init, so double check if it is.
}

void	ft_usleep(int time)
{
	int	iteration;

	iteration  = time * 2;
	printf("Iteration is %d\n", iteration);
	while(iteration--)
		usleep(500);
}
/*
void	*eat_sleep_think(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	(void)p;
	pthread_mutex_lock(&t->fork_state_mutex);
	if (t->fork_state[0] == 1 && t->fork_state[1] == 1)
	{
		t->fork_state[0] = 0;
		printf("%ld ms: Someone has taken a fork.\n", get_relative_time(t->start_time));
		//t->fork_state[1] = 0;
		printf("%ld ms: Someone has taken a fork.\n", get_relative_time(t->start_time));
		printf("%ld ms: Someone is eating.\n", get_relative_time(t->start_time));
		usleep(t->time_to_sleep * 1000);
		printf("%ld ms: Someone is thinking.\n", get_relative_time(t->start_time));
		t->fork_state[0] = 1;
		t->fork_state[1] = 1;
		pthread_mutex_unlock(&t->fork_state_mutex);
	}
	printf("%ld ms: Someone is sleeping.\n", get_relative_time(t->start_time));
	usleep(t->time_to_sleep * 1000);
	return (NULL);
}
*/
void	*eat_sleep_think(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	pthread_mutex_lock(p->left_fork);
	pthread_mutex_lock(p->right_fork);
	usleep(200000);
	printf("%ld: Philo #%d says hello!\n", get_relative_time(p->last_eating_time), p->philo_num);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_overseer	overseer;

	if (argc < 5 || argc > 6)
		return (printf("Usage is wrong.\n"), 1);
	
	overseer.number_of_philos = ft_atoi(argv[1]);

	philo = malloc(sizeof(t_philo) * overseer.number_of_philos);

	overseer.philos = philo;

	overseer.forks = malloc(sizeof(pthread_mutex_t) * overseer.number_of_philos);

	initialize_overseer(philo, &overseer, argc, argv);

	initialize_table(philo, &overseer, argc, argv);

	create_mutexes(&overseer);

	create_threads(philo, &overseer);

	join_threads(philo, &overseer);

	destroy_mutexes(&overseer);

	return (0);
}
