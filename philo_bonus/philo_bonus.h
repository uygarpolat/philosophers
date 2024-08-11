/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:58:40 by upolat            #+#    #+#             */
/*   Updated: 2024/08/11 14:47:59 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>
# include <semaphore.h>
# include <signal.h>
# include <string.h>

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
	sem_t			**death_sem;
	sem_t			*print_sem;
	sem_t			*time_sem;
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

// Processes
void	*eat_sleep_think(void *arg);
void	initialize_overseer(t_overseer *o, int argc, char **argv);
void	initialize_table(t_philo *p, t_overseer *o, char **argv);
void	create_processes(t_philo *p, t_overseer *o);
void	ft_overseer(t_overseer *o);
void	terminate_processes(t_overseer *o);

// Semaphores
int		initiate_sems(t_overseer *o);
void	destroy_sems_and_free_pids(t_overseer *o);

// Process IDs
int		handle_pids(t_overseer *overseer);
int		wait_for_children(t_overseer *t);

// Time
void	ft_usleep(size_t milisecs, t_philo *p);
size_t	what_time_is_it(void);

// Utils
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);
int		ft_is_pos_num(char *str);

#endif
