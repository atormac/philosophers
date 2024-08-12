/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:05:47 by atorma            #+#    #+#             */
/*   Updated: 2024/08/07 13:46:02 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <sys/time.h>

void	print_message(t_philo *philo, int state)
{
	char	*msg;

	if (state == STATE_DEAD)
		msg = "died";
	else if (state == STATE_THINK)
		msg = "is thinking";
	else if (state == STATE_EAT)
		msg = "is eating";
	else if (state == STATE_SLEEP)
		msg = "is sleeping";
	else
		msg = "has taken a fork";
	pthread_mutex_lock(philo->mutex);
	if (!philo->main->stopped)
		printf("%lld %zu %s\n", timestamp_ms(), philo->number, msg);
	pthread_mutex_unlock(philo->mutex);
}
