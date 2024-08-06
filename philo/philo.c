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

void	sleep_ms(int milliseconds);
long long	timestamp_ms();
void	print_message(t_philo *philo, int state);

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	print_message(philo, STATE_TOOK_FORK);
	pthread_mutex_lock(philo->fork_right);
	print_message(philo, STATE_TOOK_FORK);
	return (1);
}

void	eat_meal(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex);
	philo->meals_eaten++;
	philo->last_ate = timestamp_ms();
	pthread_mutex_unlock(philo->mutex);
	print_message(philo, STATE_EAT);
	sleep_ms(philo->time_eat);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

void	*routine(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *)ptr;
	if ((philo->number % 2)  == 0)
		sleep_ms(10);
	while (1)
	{
		take_forks(philo);
		eat_meal(philo);
		print_message(philo, STATE_SLEEP);
		sleep_ms(philo->time_sleep);
		print_message(philo, STATE_THINK);
	}
	return (NULL);
}

int	philo_threads(t_main *m, t_philo *philos)
{
	size_t	i;

	i = 0;
	while (i < m->count)
	{
		if (pthread_create(&philos[i].thid, NULL, routine, &philos[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}


int	has_died(t_philo *philo)
{
	long long	delta;
	long long	ms;

	if (philo->last_ate <= 0)
		return (0);
	ms = timestamp_ms();
	delta = ms - philo->last_ate;
	if (delta < philo->time_die)
		return (0);
	printf("%lld %zu died\n", ms, philo->number);
	return (1);
}

int	philo_observe(t_main *m, t_philo *philos)
{
	size_t	i;
	size_t	limit_reached;

	i = 0;
	limit_reached = 0;
	pthread_mutex_lock(&m->mutex);
	while (i < m->count)
	{
		if (has_died(&philos[i]))
			return (0);
		if (m->meals_limit && philos[i].meals_eaten >= m->meals_limit)
			limit_reached++;
		i++;
	}
	pthread_mutex_unlock(&m->mutex);
	if (limit_reached == m->count)
		return (0);
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
	while (1)
	{
		if (!philo_observe(m, philos))
			break;
	}
	printf("SIMULATION END\n");
	uninit(m, philos);
	return (ret);
}
