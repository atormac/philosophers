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

void	sleep_ms(int milliseconds)
{
	unsigned int	ms;

	ms = milliseconds * 1000;
	usleep(ms);
}

void	*routine(void *arg)
{
	t_philo *p;

	p = (t_philo *)arg;
	sleep_ms(1000);
	printf("philo->number: %zu\n", p->number);
	return (arg);
}

int	philo_init(t_philo *philos, t_philo *p)
{
	size_t	i;

	i = 0;
	while (i < p->count)
	{
		memcpy(&philos[i], p, sizeof(t_philo));
		philos[i].number = i + 1;
		if (pthread_mutex_init(&philos[i].fork, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	philo_threads(t_philo *philos, t_philo *p)
{
	size_t	i;
	void	*ret;

	i = 0;
	while (i < p->count)
	{
		if (pthread_create(&philos[i].thid, NULL, routine, &philos[i]) != 0)
			return (0);
		i++;
	}
	i = 0;
	while (i < p->count)
	{
		if (pthread_join(philos[i].thid, &ret) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	philo_run(t_philo *p)
{
	t_philo* philos;
	int		ret;

	philos = malloc((p->count * sizeof(t_philo)));
	if (!philos)
		return (0);
	philo_init(philos, p);
	ret = philo_threads(philos, p);
	free(philos);
	return (ret);
}
