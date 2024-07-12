/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 00:31:07 by upolat            #+#    #+#             */
/*   Updated: 2024/07/13 02:03:38 by upolat           ###   ########.fr       */
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

size_t	what_time_is_it(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}


void	ft_usleep(size_t milisecs)
{
	size_t	start;

	start = what_time_is_it();
	while ((what_time_is_it() - start) < milisecs)
		usleep(400);
}

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

void	initialize_overseer(t_overseer *o, int argc, char **argv)
{
	o->death = 0;
	o->time_to_die = ft_atoi(argv[2]);
	if (argc == 6)
		o->must_eat_amount = ft_atoi(argv[5]);
	else
		o->must_eat_amount = INT_MAX;	
}

void	initialize_table(t_philo *p, t_overseer *o, char **argv)
{
	int	i;
	
	i = 0;
	while (i < o->number_of_philos)
	{
		//p[i].number_of_philos = ft_atoi(argv[1]);
		//p[i].number_of_forks = ft_atoi(argv[1]);
		p[i].philo_num = i + 1;
		//p[i].time_to_die = ft_atoi(argv[2]);
		p[i].time_to_eat = ft_atoi(argv[3]) * 1000;
		p[i].time_to_sleep = ft_atoi(argv[4]) * 1000;
		p[i].left_fork = &o->forks[i];
		p[i].right_fork = &o->forks[(i + 1) % o->number_of_philos];
		p[i].write_mutex = &o->write_mutex;
		p[i].death_mutex = &o->death_mutex;
		p[i].death = &o->death;
		gettimeofday(&p[i].last_eating_time, NULL);
		gettimeofday(&p[i].last_eating_time2, NULL);
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

void	ft_usleep2(int time)
{
	int	iteration;

	iteration  = time * 2;
	//printf("Iteration is %d\n", iteration);
	while(iteration--)
		usleep(500);
}

void *eat_sleep_think2(void *arg) {
    t_philo *p = (t_philo *)arg;
    pthread_mutex_t *first_fork, *second_fork;

    while (1) {
        printf("Philo #%d trying to pick up first fork\n", p->philo_num);
        first_fork = (p->philo_num % 2 == 0) ? p->right_fork : p->left_fork;
        pthread_mutex_lock(first_fork);
        printf("Philo #%d picked up first fork\n", p->philo_num);

        printf("Philo #%d trying to pick up second fork\n", p->philo_num);
        second_fork = (p->philo_num % 2 == 0) ? p->left_fork : p->right_fork;
        pthread_mutex_lock(second_fork);
        printf("Philo #%d picked up second fork\n", p->philo_num);

        // Eating
        usleep(200000);  // simulate eating
        printf("%ld: Philo #%d woke up and says hello!\n", get_relative_time(p->last_eating_time), p->philo_num);
        
        pthread_mutex_unlock(second_fork);
        pthread_mutex_unlock(first_fork);
        printf("Philo #%d released both forks\n", p->philo_num);
    }
    return NULL;
}


void	*eat_sleep_think(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	
	while (1)
	{
		//if (p->philo_num % 2 == 0)
		//	usleep(100);
		printf("%ld %d is thinking\n", get_relative_time(p->last_eating_time), p->philo_num);
		pthread_mutex_lock(p->left_fork);
		printf("%ld %d has taken a fork\n", get_relative_time(p->last_eating_time), p->philo_num);
		pthread_mutex_lock(p->right_fork);
		printf("%ld %d has taken a fork\n", get_relative_time(p->last_eating_time), p->philo_num);
		printf("%ld %d is eating\n", get_relative_time(p->last_eating_time), p->philo_num);
		gettimeofday(&p->last_eating_time2, NULL);
		usleep(p->time_to_eat);
		pthread_mutex_unlock(p->right_fork);
		pthread_mutex_unlock(p->left_fork);
		printf("%ld %d is sleeping\n", get_relative_time(p->last_eating_time), p->philo_num);
		usleep(p->time_to_sleep);
	}
	return (NULL);
}

void *eat_sleep_think3(void *arg) {
    t_philo *p = (t_philo *)arg;
    pthread_mutex_t *first_fork;
    pthread_mutex_t *second_fork;

    while (1) {
        if (p->philo_num % 2 == 0) {  // If last philosopher
            first_fork = p->right_fork;  // Pick the lower-numbered fork first (1)
            second_fork = p->left_fork;  // Then the higher (5)
        } else {
            first_fork = p->left_fork;  // Lower-numbered fork
            second_fork = p->right_fork;  // Higher-numbered fork
        }

        pthread_mutex_lock(first_fork);
        pthread_mutex_lock(second_fork);

        // Eating
        usleep(200000);  // simulate eating
        printf("%ld: Philo #%d woke up and says hello!\n", get_relative_time(p->last_eating_time), p->philo_num);
        
        pthread_mutex_unlock(first_fork);
        pthread_mutex_unlock(second_fork);
    }
    return NULL;
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

	initialize_overseer(&overseer, argc, argv);

	initialize_table(philo, &overseer, argv);

	create_mutexes(&overseer);

	create_threads(philo, &overseer);

	//ft_overseer(&overseer);

	join_threads(philo, &overseer);

	destroy_mutexes(&overseer);

	return (0);
}
