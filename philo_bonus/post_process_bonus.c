/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:23:55 by upolat            #+#    #+#             */
/*   Updated: 2024/07/24 13:02:09 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	destroy_sems_and_free_pids(t_overseer *o)
{
	if (sem_close(o->fork_sem) != 0)
		ft_putstr_fd("fork_sem close failed.\n", 2);
	if (sem_close(o->print_sem) != 0)
		ft_putstr_fd("print_sem close failed.\n", 2);
	if (sem_close(o->death_sem) != 0)
		ft_putstr_fd("death_sem close failed.\n", 2);
	if (sem_close(o->terminate_sem) != 0)
		ft_putstr_fd("terminate_sem close failed.\n", 2);
	if (sem_close(o->time_sem) != 0)
		ft_putstr_fd("time_sem close failed.\n", 2);
	if (sem_close(o->write_sem) != 0)
		ft_putstr_fd("write_sem close failed.\n", 2);
	if (sem_unlink("fork_sem") != 0)
		ft_putstr_fd("fork_sem unlink failed.\n", 2);
	if (sem_unlink("print_sem") != 0)
		ft_putstr_fd("print_sem unlink failed.\n", 2);
	if (sem_unlink("death_sem") != 0)
		ft_putstr_fd("death_sem unlink failed.\n", 2);
	if (sem_unlink("terminate_sem") != 0)
		ft_putstr_fd("terminate_sem unlink failed.\n", 2);
	if (sem_unlink("time_sem") != 0)
		ft_putstr_fd("time_sem unlink failed.\n", 2);
	if (sem_unlink("write_sem") != 0)
		ft_putstr_fd("write_sem unlink failed.\n", 2);
	free(o->pid);
}

int	pid_wait(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

int	wait_for_children(t_overseer *t)
{
	int	i;
	int	final_exit_status;

	i = -1;
	final_exit_status = 0;
	while (++i < t->number_of_philos)
		final_exit_status = pid_wait(t->pid[i]);
	return (final_exit_status);
}

void	terminate_processes(t_overseer *o)
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
