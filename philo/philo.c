/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:07:57 by atorma            #+#    #+#             */
/*   Updated: 2024/07/29 16:20:00 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	*thread(void *arg)
{
	write(1, "thread\n", sizeof("thread\n") - 1);
	return (arg);
}

int	philo_threads_create(t_philo *p)
{
	pthread_t thid;
	void	*ret;
	size_t	i;

	i = 0;
	while (i < p->number)
	{
		pthread_create(&thid, NULL, thread, NULL);
		i++;
	}
	i = 0;
	while (i < p->number)
	{
		pthread_join(thid, &ret);
		i++;
	}
	printf("Finished...\n");
	(void)p;
	return (1);
}
