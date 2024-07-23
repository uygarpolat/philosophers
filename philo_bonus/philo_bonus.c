/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 00:31:07 by upolat            #+#    #+#             */
/*   Updated: 2024/07/23 02:44:12 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	handle_memory(t_overseer *o)
{
/*	*philo = malloc(sizeof(t_philo) * o->number_of_philos);
	if (*philo == NULL)
		return (0);
	o->forks = malloc(sizeof(sem_t) * o->number_of_philos);
	if (o->forks == NULL)
	{
		free(*philo);
		return (0);
	}
	o->write_mutex = malloc(sizeof(sem_t) * o->number_of_philos);
	if (o->write_mutex == NULL)
	{
		free(*philo);
		free(o->forks);
		return (0);
	}
	o->time_mutex = malloc(sizeof(sem_t) * o->number_of_philos);
	if (o->time_mutex == NULL)
	{
		free(*philo);
		free(o->forks);
		free(o->write_mutex);
		return (0);
	} */
	o->pid = malloc(sizeof(pid_t) * o->number_of_philos); // Do error check.
	return (1);
}

int	semunlinker(void)
{
	if (sem_unlink("fork_sem") != 0 || sem_unlink("print_sem") != 0)
	{
		printf("Error: sem_unlink (forks)\n");
		return (1);
	}
	if (sem_unlink("death_sem") != 0 || sem_unlink("terminate_sem") != 0)
	{
		printf("Error: sem_unlink (death)\n");
		return (1);
	}
	if (sem_unlink("time_sem") != 0 || sem_unlink("write_sem") != 0)
	{
		printf("Error: sem_unlink (time)\n");
		return (1);
	}
	return (0);
}

int	semdestroyer(t_overseer *o)
{
	if (sem_close(o->fork_sem) != 0 || sem_close(o->print_sem) != 0)
	{
		printf("Error: sem_close (forks)\n");
		return (1);
	}
	if (sem_close(o->death_sem) != 0 || sem_close(o->terminate_sem) != 0)
	{
		printf("Error: sem_close (death)\n");
		return (1);
	}
	if (sem_close(o->time_sem) != 0 || sem_close(o->write_sem) != 0)
	{
		printf("Error: sem_close (time)\n");
		return (1);
	}
	if (semunlinker() == 1)
		return (1);
	return (0);
}

static int	pid_wait(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

static int	wait_for_children(t_overseer *t)
{
	int	i;
	int	final_exit_status;

	i = -1;
	final_exit_status = 0;
	while (++i < t->number_of_philos)
		final_exit_status = pid_wait(t->pid[i]);
	return (final_exit_status);
}
/*
static void	terminate_processes(t_overseer *o)
{
	int		i;
	
	i = -1;
	//while (i--)
	sem_wait(o->terminate_sem);
	while (++i < o->number_of_philos)
		kill(o->pid[i], SIGKILL);
}
*/
int	main(int argc, char **argv)
{
	t_philo		philo;
	t_overseer	overseer;

	if (argc < 5 || argc > 6 || !validity_check(argc, argv))
		return (write(2, "Usage error.\n", 13), 1);
	overseer.number_of_philos = ft_atoi(argv[1]);
	if (!handle_memory(&overseer))
		return (write(2, "Failed to allocate memory.\n", 27), 1);
	overseer.philos = &philo;
	if (initiate_sems(&overseer))
	{
		//free_malloc(philo, &overseer);
		//write(2, "Failed to initialize mutex.\n", 28);
		return (1);
	}
	initialize_overseer(&overseer, argc, argv);
	initialize_table(&philo, &overseer, argv);
	if (!create_threads(&philo, &overseer))
		return (write(2, "Failed to create threads.\n", 26), 1);
	wait_for_children(&overseer);
	printf("All children arrived!\n");
	//terminate_processes(&overseer);
	//wait_for_children(&overseer);
	free(overseer.pid);
	semdestroyer(&overseer);
	//ft_overseer(&overseer);
	//join_threads(philo, &overseer);
	//free_and_destroy_mutexes(philo, &overseer);
	return (0);
}
