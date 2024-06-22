/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:58:40 by upolat            #+#    #+#             */
/*   Updated: 2024/06/22 15:39:43 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

typedef struct s_table
{
	int				number_of_philos;
	int				number_of_forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_amount;
	int				fork_state[2];
	pthread_mutex_t	fork_state_mutex;
	struct timeval	start_time;
}					t_table;

#endif
