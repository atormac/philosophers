/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:09:48 by atorma            #+#    #+#             */
/*   Updated: 2024/07/29 16:17:26 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

typedef struct t_philo
{
	size_t	number;
	size_t	time_die;
	size_t	time_eat;
	size_t	time_sleep;
	size_t	count_eat;
	int		is_opt;
}	t_philo;

size_t	ft_atoi(const char *s, int *error);
int		philo_threads_create(t_philo *p);

#endif
