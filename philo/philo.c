/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:07:57 by atorma            #+#    #+#             */
/*   Updated: 2024/07/29 17:46:26 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

void	*routine(void *arg)
{
	t_philo *p;

	p = (t_philo *)arg;
	printf("philo->number: %zu\n", p->number);
	return (arg);
}

int	philo_threads(t_philo *philos, t_philo *p)
{
	size_t	i;
	void	*ret;

	i = 0;
	while (i < p->count)
	{
		memcpy(&philos[i], p, sizeof(t_philo));
		philos[i].number = i + 1;
		if (pthread_create(&philos[i].thid, NULL, routine, &philos[i]) != 0)
			return (0);
		i++;
	}
	i = 0;
	while (i < p->count)
	{
		if (pthread_join(philos[i].thid, &ret) == 0)
			return (0);
		i++;
	}
	return (1);
	
}

int	philo_run(t_philo *p)
{
	t_philo* philos;

	philos = malloc((p->count * sizeof(t_philo)));
	if (!philos)
		return (0);
	philo_threads(philos, p);
	free(philos);
	return (1);
}
