/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 00:31:07 by upolat            #+#    #+#             */
/*   Updated: 2024/06/21 00:54:26 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// Function to print the current time
void print_timestamp(const char *msg)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	printf("%s: %ld.%06d\n", msg, tv.tv_sec, tv.tv_usec);
}

// Function to be executed by the thread
void *thread_function(void *arg)
{
	(void)arg;
	print_timestamp("This gets printed first: This is the thread");
	return NULL;
}

int main(void)
{
	pthread_t thread;

	// Create a new thread
	if (pthread_create(&thread, NULL, thread_function, NULL) != 0)
	{
		perror("pthread_create");
		return 1;
	}

	print_timestamp("Will this get printed out first or second? Should be second");

	if (pthread_join(thread, NULL) != 0)
	{
		perror("pthread_join");
		return 1;
	}

	print_timestamp("This is the main thread. This will for sure get printed out the last");

	return 0;
}

