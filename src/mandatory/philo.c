/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 00:31:07 by upolat            #+#    #+#             */
/*   Updated: 2024/07/17 18:03:47 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_is_pos_num(char *str)
{
	int	i;

	if (!ft_strncmp(str, "+", 2) || !ft_strncmp(str, "-", 2))
		return (0);
	i = 0;
	if (ft_strlen(str) == 0)
		return (0);
	while (str[i])
	{
		if ((str[i] != '-' || i != 0) && (str[i] != '+'
				|| i != 0) && (str[i] < '0' || str[i] > '9'))
			return (0);
		i++;
	}
	if (ft_atoi(str) <= 0)
		return (0);
	else
		return (1);
}

int	validity_check(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!ft_is_pos_num(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

size_t	what_time_is_it_us(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000 + time.tv_usec);
}

void	ft_usleep(size_t milisecs, int number_of_philos)
{
	size_t	start;
	size_t	nanosecs;

	nanosecs = milisecs * 1000;
	start = what_time_is_it_us();
	while ((what_time_is_it_us() - start) < nanosecs)
		usleep(2 * number_of_philos);
}

size_t	get_relative_time(struct timeval start_time)
{
	struct timeval	current_time;
	long			seconds;
	long			useconds;

	gettimeofday(&current_time, NULL);
	seconds = current_time.tv_sec - start_time.tv_sec;
	useconds = current_time.tv_usec - start_time.tv_usec;
	if (useconds < 0)
	{
		seconds -= 1;
		useconds += 1000000;
	}
	return ((seconds * 1000) + (useconds / 1000));
}

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
	int	i;

	i = 0;
	while (i < o->number_of_philos)
	{
		p[i].philo_num = i + 1;
		p[i].number_of_philos = ft_atoi(argv[1]);
		p[i].time_to_eat = ft_atoi(argv[3]);
		p[i].time_to_sleep = ft_atoi(argv[4]);
		p[i].ate = 0;
		p[i].left_fork = &o->forks[i];
		p[i].right_fork = &o->forks[(i + 1) % o->number_of_philos];
		p[i].write_mutex = &o->write_mutex[i];
		p[i].death_mutex = &o->death_mutex;
		p[i].time_mutex = &o->time_mutex;
		p[i].death = &o->death;
		//gettimeofday(&p[i].last_eating_time, NULL);
		//gettimeofday(&p[i].last_eating_time2, NULL);
		i++;
	}
}

void	create_threads(t_philo *p, t_overseer *o)
{
	int				i;
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	i = 0;
	while (i < o->number_of_philos)
	{
		p[i].last_eating_time = start_time;
		p[i].last_eating_time2 = start_time;
		if (pthread_create(&p[i].thread, NULL,
				eat_sleep_think, (void *)&p[i]) != 0)
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

	i = -1;
	while (++i < o->number_of_philos)
		pthread_join(p[i].thread, NULL);
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
	i = 0;
	while (i < o->number_of_philos)
	{
		if (pthread_mutex_destroy(&o->write_mutex[i]) != 0)
		{
			perror("pthread_mutex_destroy error");
			return ;
		}
		i++;
	}

	//if (pthread_mutex_destroy(&o->write_mutex) != 0)
	//{
	//	perror("pthread_mutex_destroy error");
	//	return ;
	//}
	if (pthread_mutex_destroy(&o->death_mutex) != 0)
	{
		perror("pthread_mutex_destroy error");
		return ;
	}
	if (pthread_mutex_destroy(&o->time_mutex) != 0)
	{
		perror("pthread_mutex_destroy error");
		return ;
	}
	// Is checking if it is equal to zero how you handle errors in destroying?
	// It was copy/pasted from the init function, so double check if it is.
}

void	*eat_sleep_think(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->number_of_philos == 1)
		return (NULL);
	pthread_mutex_lock(p->death_mutex);
	printf("%zu %d is thinking\n", get_relative_time(p->last_eating_time), p->philo_num);
	pthread_mutex_unlock(p->death_mutex);
	if (p->philo_num % 2 == 0 || p->philo_num == p->number_of_philos)
		ft_usleep(p->time_to_eat / 10, p->number_of_philos);
	while (1)
	{
		pthread_mutex_lock(p->left_fork);
		pthread_mutex_lock(p->death_mutex);
		if (!*p->death)
			printf("%zu %d has taken a fork\n", get_relative_time(p->last_eating_time), p->philo_num);
		pthread_mutex_unlock(p->death_mutex);
		pthread_mutex_lock(p->right_fork);
		pthread_mutex_lock(p->death_mutex);
		if (!*p->death)
			printf("%zu %d has taken a fork\n", get_relative_time(p->last_eating_time), p->philo_num);
		pthread_mutex_unlock(p->death_mutex);
		pthread_mutex_lock(p->death_mutex);
		if (!*p->death)
			printf("%zu %d is eating\n", get_relative_time(p->last_eating_time), p->philo_num);
		pthread_mutex_unlock(p->death_mutex);
		//pthread_mutex_lock(p->time_mutex);
		//gettimeofday(&p->last_eating_time2, NULL);
		//pthread_mutex_unlock(p->time_mutex);
		pthread_mutex_lock(p->write_mutex);
		gettimeofday(&p->last_eating_time2, NULL);
		p->ate++;
		pthread_mutex_unlock(p->write_mutex);
		ft_usleep(p->time_to_eat, p->number_of_philos);
		pthread_mutex_lock(p->death_mutex);
		if (!*p->death)
			printf("%zu %d is sleeping\n", get_relative_time(p->last_eating_time), p->philo_num);
		pthread_mutex_unlock(p->death_mutex);
		//pthread_mutex_lock(p->write_mutex);
		//p->ate++;
		//pthread_mutex_unlock(p->write_mutex);
		pthread_mutex_unlock(p->right_fork);
		pthread_mutex_unlock(p->left_fork);
		ft_usleep(p->time_to_sleep, p->number_of_philos);
		pthread_mutex_lock(p->death_mutex);
		if (!*p->death)
			printf("%zu %d is thinking\n", get_relative_time(p->last_eating_time), p->philo_num);
		pthread_mutex_unlock(p->death_mutex);
		pthread_mutex_lock(p->death_mutex);
		if (*p->death)
		{
			pthread_mutex_unlock(p->death_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(p->death_mutex);
	}
	return (NULL);
}

int	everyone_ate(t_overseer *o)
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

void	ft_overseer(t_overseer *o)
{
	int		i;
	size_t	time_since_start_of_meal;

	while (1)
	{
		i = -1;
		while (++i < o->number_of_philos)
		{
			pthread_mutex_lock(&o->write_mutex[i]);
			time_since_start_of_meal = get_relative_time
				(o->philos[i].last_eating_time2);
			pthread_mutex_unlock(&o->write_mutex[i]);
			if (time_since_start_of_meal >= o->time_to_die)
			{
				pthread_mutex_lock(&o->death_mutex);
				o->death = 2;
				pthread_mutex_unlock(&o->death_mutex);
				printf("%zu %d died\n", get_relative_time
					(o->philos[i].last_eating_time), i + 1);
				return ;
			}
			if (everyone_ate(o))
				return ;
		}
	}
}

int	handle_memory(t_philo **philo, t_overseer *overseer)
{
	*philo = malloc(sizeof(t_philo) * overseer->number_of_philos);
	if (*philo == NULL)
		return (0);
	overseer->forks = malloc(sizeof(pthread_mutex_t)
			* overseer->number_of_philos);
	if (overseer->forks == NULL)
	{
		free(*philo);
		return (0);
	}
	overseer->write_mutex = malloc(sizeof(pthread_mutex_t) * overseer->number_of_philos);
	if (overseer->write_mutex == NULL)
	{
		free(*philo);
		free(overseer->forks);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_overseer	overseer;

	if (argc < 5 || argc > 6 || !validity_check(argc, argv))
		return (write(2, "Usage error.\n", 13), 1);
	overseer.number_of_philos = ft_atoi(argv[1]);
	philo = NULL;
	if (!handle_memory(&philo, &overseer))
		return (write(2, "Memory allocation failed.\n", 26), 1);
	overseer.philos = philo;
	if (!create_mutexes(&overseer))
		return (write(2, "Failed to initialize mutex.\n", 28), 1);
	initialize_overseer(&overseer, argc, argv);
	initialize_table(philo, &overseer, argv);
	create_threads(philo, &overseer);
	ft_overseer(&overseer);
	join_threads(philo, &overseer);
	destroy_mutexes(&overseer);
	free(philo);
	free(overseer.forks);
	free(overseer.write_mutex);
	return (0);
}
