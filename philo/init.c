/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:33:29 by atorma            #+#    #+#             */
/*   Updated: 2024/08/07 14:22:52 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

int	init(t_philo *philos, t_main *m)
{
	size_t	i;

	m->stopped = 0;
	if (pthread_mutex_init(&m->mutex, NULL) != 0)
		return (0);
	i = 0;
	while (i < m->count)
	{
		if (pthread_mutex_init(&philos[i].fork, NULL) != 0)
			return (0);
		philos[i].number = i + 1;
		philos[i].main = m;
		philos[i].meals_eaten = 0;
		philos[i].last_ate = 0;
		philos[i].mutex = &m->mutex;
		philos[i].fork_left = &philos[i].fork;
		philos[i].fork_right = &philos[(i + 1) % m->count].fork;
		if (i % 2)
		{
			philos[i].fork_left = &philos[(i + 1) % m->count].fork;
			philos[i].fork_right = &philos[i].fork;
		}
		i++;
	}
	return (1);
}

void	uninit(t_main *m, t_philo *philos)
{
	size_t	i;

	i = 0;
	while (i < m->count)
	{
		pthread_join(philos[i].thid, NULL);
		pthread_detach(philos[i].thid);
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
