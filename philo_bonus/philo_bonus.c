/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 00:31:07 by upolat            #+#    #+#             */
/*   Updated: 2024/07/24 03:43:36 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	destroy_sems_and_free_pids(t_overseer *o)
{
	if (sem_close(o->fork_sem) != 0)
		write(2, "fork_sem close failed!\n", 23);
	if (sem_close(o->print_sem) != 0)
		write(2, "print_sem close failed!\n", 24);
	if (sem_close(o->death_sem) != 0)
		write(2, "death_sem close failed!\n", 24);
	if (sem_close(o->terminate_sem) != 0)
		write(2, "terminate_sem close failed!\n", 28);
	if (sem_close(o->time_sem) != 0)
		write(2, "time_sem close failed!\n", 23);
	if (sem_close(o->write_sem) != 0)
		write(2, "write_sem close failed!\n", 24);
	if (sem_unlink("fork_sem") != 0)
		write(2, "fork_sem unlink failed.\n", 24);
	if (sem_unlink("print_sem") != 0)
		write(2, "print_sem unlink failed.\n", 25);
	if (sem_unlink("death_sem") != 0)
		write(2, "death_sem unlink failed.\n", 25);
	if (sem_unlink("terminate_sem") != 0)
		write(2, "terminate_sem unlink failed.\n", 29);
	if (sem_unlink("time_sem") != 0)
		write(2, "time_sem unlink failed.\n", 24);
	if (sem_unlink("write_sem") != 0)
		write(2, "write_sem unlink failed.\n", 25);
	free(o->pid);
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

static void	terminate_processes(t_overseer *o)
{
	int		i;

	i = o->number_of_philos;
	while (i--)
		sem_wait(o->terminate_sem);
	while (++i < o->number_of_philos)
	{
		if (o->pid[i] > 0)
			kill(o->pid[i], SIGKILL);
	}
}

int	main(int argc, char **argv)
{
	t_philo		philo;
	t_overseer	overseer;

	if (argc < 5 || argc > 6 || !validity_check(argc, argv))
		return (write(2, "Usage error.\n", 13), 1);
	overseer.number_of_philos = ft_atoi(argv[1]);
	overseer.pid = malloc(sizeof(pid_t) * overseer.number_of_philos);
	if (overseer.pid == NULL)
		return (write(2, "Failed to allocate memory.\n", 27), 1);
	memset(overseer.pid, -1, sizeof(pid_t) * overseer.number_of_philos);
	overseer.philos = &philo;
	if (initiate_sems(&overseer))
	{
		free(overseer.pid);
		write(2, "Failed to initialize semaphores.\n", 34);
		return (1);
	}
	initialize_overseer(&overseer, argc, argv);
	initialize_table(&philo, &overseer, argv);
	if (!create_processes(&philo, &overseer))
		return (write(2, "Failed to create threads.\n", 26), 1);
	terminate_processes(&overseer);
	wait_for_children(&overseer);
	destroy_sems_and_free_pids(&overseer);
	return (0);
}
