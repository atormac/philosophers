/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:07:57 by atorma            #+#    #+#             */
/*   Updated: 2024/08/07 17:37:46 by atorma           ###   ########.fr       */
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
	time_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time_ms);
}

void	philo_sleep(t_philo *philo, long long ms)
{
	long long	time_till;

	time_till = timestamp_ms() + ms;
	while (timestamp_ms() < time_till)
	{
		usleep(500);
		pthread_mutex_lock(philo->mutex);
		if (philo->main->stopped)
		{
			pthread_mutex_unlock(philo->mutex);
			break ;
		}
		pthread_mutex_unlock(philo->mutex);
	}
}

int	philo_threads(t_main *m, t_philo *philos)
{
	size_t	i;

	i = 0;
	while (i < m->count)
	{
		if (pthread_create(&philos[i].thid, NULL,
				thread_routine, &philos[i]) != 0)
		{
			return (0);
		}
		i++;
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
	while (monitor(m, philos))
		usleep(1 * 1000);
	uninit(m, philos);
	return (ret);
}
