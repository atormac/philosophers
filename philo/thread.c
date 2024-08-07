/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:30:31 by atorma            #+#    #+#             */
/*   Updated: 2024/08/07 15:41:42 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	if (philo->number % 2 == 0 && philo->meals_eaten == 0)
	{
		pthread_mutex_lock(philo->fork_right);
		print_message(philo, STATE_TOOK_FORK);
		pthread_mutex_lock(philo->fork_left);
		print_message(philo, STATE_TOOK_FORK);
	}
	else
	{
		pthread_mutex_lock(philo->fork_left);
		print_message(philo, STATE_TOOK_FORK);
		pthread_mutex_lock(philo->fork_right);
		print_message(philo, STATE_TOOK_FORK);
	}
}

static void	eat_meal(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex);
	philo->meals_eaten++;
	philo->last_ate = timestamp_ms();
	pthread_mutex_unlock(philo->mutex);
	print_message(philo, STATE_EAT);
	sleep_ms(philo->main->time_eat);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

static void	*single_philo(t_philo *philo)
{
	print_message(philo, STATE_TOOK_FORK);
	sleep_ms(philo->main->time_die);
	print_message(philo, STATE_DEAD);
	pthread_mutex_lock(philo->mutex);
	philo->main->stopped = 1;
	pthread_mutex_unlock(philo->mutex);
	return (NULL);
}

void	*thread_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->main->count == 1)
		return (single_philo(philo));
	if (philo->number % 2 == 0)
	{
		sleep_ms(philo->main->time_sleep);
		print_message(philo, STATE_THINK);
	}
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
