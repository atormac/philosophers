/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:07:57 by atorma            #+#    #+#             */
/*   Updated: 2024/08/14 15:23:46 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <string.h>
#include <sys/time.h>

void	*thread_routine(void *ptr);

long long	timestamp_ms(void)
{
	long long			time_ms;
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	time_ms = tv.tv_sec * 1000LL + tv.tv_usec / 1000LL;
	return (time_ms);
}

void	philo_sleep(t_philo *philo, long long ms)
{
	long long	time_till;
	long long	counter;

	time_till = timestamp_ms() + ms;
	counter = 0;
	while (timestamp_ms() < time_till)
	{
		usleep(500);
		if (counter > 500)
		{
			if (has_stopped(philo))
				break ;
			counter = 0;
		}
		counter++;
	}
}

int	philo_threads(t_main *m, t_philo *philos)
{
	m->threads_created = 0;
	while (m->threads_created < m->count)
	{
		if (pthread_create(&philos[m->threads_created].thid, NULL,
				thread_routine, &philos[m->threads_created]) != 0)
		{
			pthread_mutex_lock(&m->mutex);
			m->stopped = 1;
			printf("Error creating threads!\n");
			pthread_mutex_unlock(&m->mutex);
			return (0);
		}
		m->threads_created++;
	}
	return (1);
}

int	philo_run(t_main *m)
{
	t_philo	*philos;
	int		ret;

	philos = malloc(m->count * sizeof(t_philo));
	if (!philos || !init(philos, m))
	{
		free(philos);
		return (0);
	}
	ret = philo_threads(m, philos);
	while (ret && monitor(m, philos))
		usleep(1 * 1000);
	uninit(m, philos);
	return (ret);
}
