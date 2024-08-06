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

struct	t_main;

typedef struct t_philo
{
	int				*stop;
	size_t			number;
	size_t			meals_eaten;
	long long		last_ate;
	pthread_mutex_t *mutex;
	pthread_mutex_t	fork;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_t		thid;
	struct t_main			*main;
}	t_philo;

typedef struct	t_main
{
	int				stopped;
	size_t			count;
	size_t			meals_limit;
	long long		time_die;
	size_t			time_eat;
	size_t			time_sleep;
	pthread_mutex_t	mutex;
	t_philo			*philo;
}	t_main;


size_t	ft_atoi(const char *s, int *error);
int		init(t_philo *philos, t_philo *p, t_main *m);
void	uninit(t_main *m, t_philo *philos);
int		philo_run(t_main *m);

#endif
