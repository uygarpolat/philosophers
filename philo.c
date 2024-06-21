/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 00:31:07 by upolat            #+#    #+#             */
/*   Updated: 2024/06/21 18:39:27 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void	*thread_function(void *arg)
{
	char			*str;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	str = (char *) arg;
	printf("%s: %ld.%06d\n", str, tv.tv_sec, tv.tv_usec);
	return (NULL);
}

int	main(void)
{
	pthread_t	thread;
	char		*str;

	str = "Time of execution:";
	if (pthread_create(&thread, NULL, thread_function, (void *)str) != 0)
		return (perror("pthread_create"), 1);
	thread_function((void *)str);
	if (pthread_join(thread, NULL) != 0)
		return (perror("pthread_join"), 1);
	thread_function((void *)str);
	return (0);
}
