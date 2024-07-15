/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:58:40 by upolat            #+#    #+#             */
/*   Updated: 2024/07/14 22:02:28 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				number_of_philos;
	int				philo_num;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				*death;
	int				ate;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*write_mutex;
	pthread_mutex_t	*death_mutex;
	pthread_mutex_t	*time_mutex;
	pthread_t		thread;
	struct timeval	last_eating_time;
	struct timeval	last_eating_time2;
}					t_philo;

typedef struct s_overseer
{
	int				number_of_philos;
	int				death;
	int				must_eat_amount;
	size_t			time_to_die;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	time_mutex;
	t_philo			*philos;
}			t_overseer;

#endif
