/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:07:57 by atorma            #+#    #+#             */
/*   Updated: 2024/07/31 14:50:53 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

void	print_message(int philo_num, int state);

void	sleep_ms(int milliseconds)
{
	unsigned int	ms;

	ms = milliseconds * 1000;
	usleep(ms);
}

void	*routine(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(philo->mutex);
	sleep_ms(1000);
	print_message(philo->number, STATE_TOOK_FORK);
	pthread_mutex_unlock(philo->mutex);
	/*
	while (1)
	{
		lock_forks()
		eat()
		sleep()
		think()
	}
	*/
	return (NULL);
}

int	philo_threads(t_main *m, t_philo *philos)
{
	size_t	i;
	void	*ret;

	i = 0;
	while (i < m->count)
	{
		if (pthread_create(&philos[i].thid, NULL, routine, &philos[i]) != 0)
			return (0);
		i++;
	}
	i = 0;
	while (i < m->count)
	{
		if (pthread_join(philos[i].thid, &ret) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	philo_run(t_main *m)
{
	t_philo	*philos;
	t_philo	p;
	int		ret;

	philos = malloc(m->count * sizeof(t_philo));
	if (!philos || !init(philos, &p, m))
	{
		free(philos);
		return (0);
	}
	ret = philo_threads(m, philos);
	uninit(m, philos);
	return (ret);
}
