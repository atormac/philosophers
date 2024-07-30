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


void	print_message(int philo_num, int state)
{
	char	*msg;
	size_t	time_ms;
	struct	timeval tv;


	if (state == STATE_THINK)
		msg = "is thinking";
	else if (state == STATE_EAT)
		msg = "is_eating";
	else if (state == STATE_SLEEP)
		msg = "is sleeping";
	else if (state == STATE_DEAD)
		msg = "died";
	else
		msg = "unknown";
	gettimeofday(&tv, NULL);
	time_ms = (tv.tv_sec * 1000 + tv.tv_usec) / 1000;
	printf("%zu %d %s\n", time_ms, philo_num, msg);
}
