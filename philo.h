/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:58:40 by upolat            #+#    #+#             */
/*   Updated: 2024/06/27 01:44:21 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

typedef struct s_philo
{
	int				number_of_philos;
	int				number_of_forks;
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_amount;
	pthread_mutex_t	fork_state_mutex;
	pthread_t		thread;
	struct timeval	last_eating_time;
}					t_philo;

typedef struct s_overseer
{
	int		number_of_philos;
}			t_overseer;

#endif
