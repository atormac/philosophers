/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:07:57 by atorma            #+#    #+#             */
/*   Updated: 2024/07/29 17:00:21 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

void	*thread(void *arg)
{
	t_philo *p;

	p = (t_philo *)arg;
	printf("philo->number: %zu\n", p->number);
	return (arg);
}

int	philo_threads_create(t_philo *p)
{
	t_philo* philos;
	void	*ret;
	size_t	i;

	philos = malloc((p->count * sizeof(t_philo)));
	if (!philos)
		return (0);
	i = 0;
	while (i < p->count)
	{
		memcpy(&philos[i], p, sizeof(t_philo));
		philos[i].number = i + 1;
		pthread_create(&philos[i].thid, NULL, thread, &philos[i]);
		i++;
	}
	i = 0;
	while (i < p->count)
	{
		pthread_join(philos[i].thid, &ret);
		i++;
	}
	free(philos);
	return (1);
}
