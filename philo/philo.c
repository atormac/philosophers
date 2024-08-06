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
	return (NULL);
}

int	philo_init(t_philo *philos, t_philo *p, t_main *m)
{
	size_t	i;

	i = 0;
	if (pthread_mutex_init(&m->mutex, NULL) != 0)
		return (0);
	while (i < m->count)
	{
		memcpy(&philos[i], p, sizeof(t_philo));
		philos[i].number = i + 1;
		if (pthread_mutex_init(&philos[i].fork, NULL) != 0)
			return (0);
		printf("fork: %zu, %p\n", i, &philos[i].fork);
		i++;
	}
	i = 0;
	while (i < m->count)
	{
		philos[i].mutex = &m->mutex;
		philos[i].fork_left = &philos[i].fork;
		philos[i].fork_right = &philos[(i + 1) % m->count].fork;
		printf("philo: %zu, fork_left: %p, fork_right: %p\n",
				philos[i].number, philos[i].fork_left, philos[i].fork_right);
		i++;
	}
	return (1);
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
	if (!philos || !philo_init(philos, &p, m))
	{
		printf("Failed to initialize philos!\n");
		free(philos);
		return (0);
	}
	ret = philo_threads(m, philos);
	free(philos);
	return (ret);
}
