/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:58:40 by upolat            #+#    #+#             */
/*   Updated: 2024/06/28 16:22:52 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

typedef struct s_philo
{
	int				number_of_philos;
	int				number_of_forks;
	int				philo_num;
	//int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	//int				must_eat_amount;
	int				*death;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*write_mutex;
	pthread_mutex_t	*death_mutex;
	pthread_t		thread;
	struct timeval	last_eating_time;
}					t_philo;

typedef struct s_overseer
{
	int				number_of_philos;
	int				death;
	int				must_eat_amount;
	int				time_to_die;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	death_mutex;
	t_philo	*philos;
}			t_overseer;

#endif
