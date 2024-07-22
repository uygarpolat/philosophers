/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:58:40 by upolat            #+#    #+#             */
/*   Updated: 2024/07/23 00:27:55 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_philo
{
	int				number_of_philos;
	int				philo_num;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				*death;
	int				ate;
	sem_t			*fork_sem;
	sem_t			*write_sem;
	sem_t			*death_sem;
	sem_t			*time_sem;
	sem_t			*print_sem;
	sem_t			*terminate_sem;
	pthread_t		thread;
	size_t			sim_start_time;
	size_t			last_meal_time;
}					t_philo;

typedef struct s_overseer
{
	int				number_of_philos;
	int				death;
	int				must_eat_amount;
	size_t			time_to_die;
	sem_t			*fork_sem;
	sem_t			*write_sem;
	sem_t			*death_sem;
	sem_t			*print_sem;
	sem_t			*time_sem;
	sem_t			*terminate_sem;
	pid_t			*pid;
	t_philo			*philos;
}					t_overseer;

// Mutexes
int		create_mutexes(t_overseer *o);
void	destroy_fork_mutexes(t_overseer *o);
void	destroy_write_mutexes(t_overseer *o);
void	destroy_time_mutexes(t_overseer *o);
void	free_and_destroy_mutexes(t_philo *philo, t_overseer *overseer);

// Threads
void	*eat_sleep_think(void *arg);
void	initialize_overseer(t_overseer *o, int argc, char **argv);
void	initialize_table(t_philo *p, t_overseer *o, char **argv);
int		create_threads(t_philo *p, t_overseer *o);
void	join_threads(t_philo *p, t_overseer *o);
void	ft_overseer(t_overseer *o);

// Time
void	ft_usleep(size_t milisecs, t_philo *p);
size_t	what_time_is_it(void);

// Utils
void	free_malloc(t_philo *philo, t_overseer *overseer);
int		ft_atoi(const char *str);
int		validity_check(int argc, char **argv);

int	initiate_sems(t_overseer *o);

#endif
