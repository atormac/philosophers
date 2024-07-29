/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:07:57 by atorma            #+#    #+#             */
/*   Updated: 2024/07/29 16:54:30 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

void	*thread(void *arg)
{
	t_philo *p;

	p = (t_philo *)arg;
	printf("philo \n");
	return (arg);
}

int	philo_threads_create(t_philo *p)
{
	t_philo* philos;
	void	*ret;
	size_t	i;

	philos = malloc((p->number * sizeof(t_philo)));
	if (!philos)
		return (0);
	i = 0;
	while (i < p->number)
	{
		memcpy(&philos[i], p, sizeof(t_philo));
		pthread_create(&philos[i].thid, NULL, thread, philos + i * sizeof(t_philo));
		i++;
	}
	i = 0;
	while (i < p->number)
	{
		pthread_join(philos[i].thid, &ret);
		i++;
	}
	free(philos);
	return (1);
}
