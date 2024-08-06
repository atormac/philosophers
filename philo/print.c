/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:05:47 by atorma            #+#    #+#             */
/*   Updated: 2024/07/30 15:56:27 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

void	sleep_ms(int milliseconds)
{
	unsigned int	ms;

	ms = milliseconds * 1000;
	usleep(ms);
}

long long	timestamp_ms()
{
	long long	time_ms;
	struct		timeval tv;

	gettimeofday(&tv, NULL);
	time_ms = (tv.tv_sec * 1000 + tv.tv_usec) / 1000;
	return (time_ms);
}

void	print_message(t_philo *philo, int state)
{
	char	*msg;

	if (state == STATE_DEAD)
		msg = "died";
	if (state == STATE_THINK)
		msg = "is thinking";
	else if (state == STATE_EAT)
		msg = "is eating";
	else if (state == STATE_SLEEP)
		msg = "is sleeping";
	else
		msg = "has taken a fork";
	
	pthread_mutex_lock(philo->mutex);
	printf("%lld %zu %s\n", timestamp_ms(), philo->number, msg);
	pthread_mutex_unlock(philo->mutex);
}
