/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:10:27 by atorma            #+#    #+#             */
/*   Updated: 2024/08/07 13:11:04 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	has_stopped(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(philo->mutex);
	ret = philo->main->stopped;
	pthread_mutex_unlock(philo->mutex);
	return (ret);
}

int	has_died(t_philo *philo)
{
	long long	delta;
	long long	ms;

	if (philo->last_ate <= 0)
		return (0);
	ms = timestamp_ms();
	delta = ms - philo->last_ate;
	if (delta < philo->main->time_die)
		return (0);
	philo->main->stopped = 1;
	printf("%lld %zu died\n", ms, philo->number);
	return (1);
}

int	philo_monitor(t_main *m, t_philo *philos)
{
	size_t	i;
	size_t	limit_reached;
	int		ret;

	i = 0;
	limit_reached = 0;
	pthread_mutex_lock(&m->mutex);
	while (i < m->count)
	{
		if (has_died(&philos[i]))
			break ;
		if (m->meals_limit && philos[i].meals_eaten >= m->meals_limit)
			limit_reached++;
		i++;
	}
	if (limit_reached == m->count)
	{
		printf("All philosophers ate %zu times\n", m->meals_limit);
		m->stopped = 1;
	}
	ret = m->stopped;
	pthread_mutex_unlock(&m->mutex);
	return (!ret);
}
