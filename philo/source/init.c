/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:33:29 by atorma            #+#    #+#             */
/*   Updated: 2024/08/14 16:06:55 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <string.h>

static int	destroy_mutexes(t_philo *philos, int i)
{
	while (i-- > 0)
		pthread_mutex_destroy(&philos[i].fork);
	return (0);
}

int	init(t_philo *philos, t_main *m)
{
	size_t	i;

	m->stopped = 0;
	if (pthread_mutex_init(&m->mutex, NULL) != 0)
		return (0);
	i = 0;
	memset(philos, 0, m->count * sizeof(t_philo));
	while (i < m->count)
	{
		if (pthread_mutex_init(&philos[i].fork, NULL) != 0)
		{
			pthread_mutex_destroy(&m->mutex);
			return (destroy_mutexes(philos, i));
		}
		philos[i].number = i + 1;
		philos[i].main = m;
		philos[i].mutex = &m->mutex;
		philos[i].fork_left = &philos[i].fork;
		philos[i].fork_right = &philos[(i + 1) % m->count].fork;
		i++;
	}
	return (1);
}

void	uninit(t_main *m, t_philo *philos)
{
	size_t	i;

	i = 0;
	while (i < m->threads_created)
	{
		pthread_join(philos[i].thid, NULL);
		i++;
	}
	i = 0;
	while (i < m->count)
	{
		pthread_mutex_destroy(&philos[i].fork);
		i++;
	}
	pthread_mutex_destroy(&m->mutex);
	free(philos);
}
