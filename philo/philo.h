/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:09:48 by atorma            #+#    #+#             */
/*   Updated: 2024/07/29 17:46:57 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

enum
{
	STATE_DEAD,
	STATE_THINK,
	STATE_SLEEP,
	STATE_TOOK_FORK,
	STATE_EAT
};

typedef struct t_philo
{
	size_t			number;
	int				is_opt;
	size_t			state;
	pthread_mutex_t *mutex;
	pthread_mutex_t	fork;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_t		thid;
}	t_philo;

typedef struct	t_main
{
	size_t			count;
	ssize_t			eat_count;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	pthread_mutex_t	mutex;
	t_philo			*philo;
}	t_main;


size_t	ft_atoi(const char *s, int *error);
int		philo_run(t_main *m);

#endif
