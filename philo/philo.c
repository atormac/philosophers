/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:07:57 by atorma            #+#    #+#             */
/*   Updated: 2024/08/07 13:14:17 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

void		print_message(t_philo *philo, int state);
int			has_stopped(t_philo *philo);
int			has_died(t_philo *philo);
int			philo_monitor(t_main *m, t_philo *philos);

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
	print_message(philo, STATE_DEAD);
	pthread_mutex_lock(philo->mutex);
	philo->main->stopped = 1;
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
