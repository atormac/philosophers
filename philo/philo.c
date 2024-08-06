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

int	has_stopped(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(philo->mutex);
	ret = philo->main->stopped;
	pthread_mutex_unlock(philo->mutex);
	return (ret);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	print_message(philo, STATE_TOOK_FORK);
	pthread_mutex_lock(philo->fork_right);
	print_message(philo, STATE_TOOK_FORK);
}

void	eat_meal(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex);
	philo->meals_eaten++;
	philo->last_ate = timestamp_ms();
	pthread_mutex_unlock(philo->mutex);
	print_message(philo, STATE_EAT);
	sleep_ms(philo->main->time_eat);
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
}

void	*single_philo(t_philo *philo)
{
	print_message(philo, STATE_TOOK_FORK);
	sleep_ms(philo->main->time_die);
	pthread_mutex_lock(philo->mutex);
	philo->main->stopped = 1;
	printf("%lld %zu died\n", timestamp_ms(), philo->number);
	pthread_mutex_unlock(philo->mutex);
	return (NULL);
}

void	*routine(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *)ptr;
	if (philo->main->count == 1)
		return (single_philo(philo));
	if ((philo->number % 2)  == 0)
		sleep_ms(10);
	while (!has_stopped(philo))
	{
		take_forks(philo);
		eat_meal(philo);
		if (has_stopped(philo))
			break ;
		print_message(philo, STATE_SLEEP);
		sleep_ms(philo->main->time_sleep);
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
	while (1)
	{
		if (!philo_monitor(m, philos))
			break;
		sleep_ms(1);
	}
	uninit(m, philos);
	printf("SIMULATION END\n");
	return (ret);
}
