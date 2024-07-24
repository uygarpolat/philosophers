/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 00:31:07 by upolat            #+#    #+#             */
/*   Updated: 2024/07/24 15:29:49 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	validity_check(int argc, char **argv)
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

int	main(int argc, char **argv)
{
	t_philo		philo;
	t_overseer	overseer;
	int			exit_code;

	if (argc < 5 || argc > 6 || !validity_check(argc, argv))
		return (ft_putstr_fd("Usage error.\n", 2), 1);
	overseer.number_of_philos = ft_atoi(argv[1]);
	if (handle_pids(&overseer))
		return (1);
	overseer.philos = &philo;
	if (initiate_sems(&overseer))
	{
		free(overseer.pid);
		overseer.pid = NULL;
		ft_putstr_fd("Failed to initialize semaphores.\n", 2);
		return (1);
	}
	initialize_overseer(&overseer, argc, argv);
	initialize_table(&philo, &overseer, argv);
	create_processes(&philo, &overseer);
	terminate_processes(&overseer);
	exit_code = wait_for_children(&overseer);
	destroy_sems_and_free_pids(&overseer);
	overseer.pid = NULL;
	return (exit_code);
}
