
#include "philo.h"
#include <string.h>

int	init(t_philo *philos, t_philo *p, t_main *m)
{
	size_t	i;

	i = 0;
	while (i < m->count)
	{
		memcpy(&philos[i], p, sizeof(t_philo));
		philos[i].number = i + 1;
		if (pthread_mutex_init(&philos[i].fork, NULL) != 0)
			return (0);
		printf("fork: %zu, %p\n", i, &philos[i].fork);
		i++;
	}
	i = 0;
	m->stopped = 0;
	while (i < m->count)
	{
		philos[i].main = m;
		philos[i].meals_eaten = 0;
		philos[i].last_ate = 0;
		philos[i].mutex = &m->mutex;
		philos[i].time_die = m->time_die;
		philos[i].time_eat = m->time_eat;
		philos[i].time_sleep = m->time_sleep;
		philos[i].fork_left = &philos[i].fork;
		philos[i].fork_right = &philos[(i + 1) % m->count].fork;
		if (i % 2)
		{
			philos[i].fork_left = &philos[(i + 1) % m->count].fork;
			philos[i].fork_right = &philos[i].fork;
		}
		printf("philo: %zu, fork_left: %p, fork_right: %p\n",
				philos[i].number, philos[i].fork_left, philos[i].fork_right);
		i++;
	}
	if (pthread_mutex_init(&m->mutex, NULL) != 0)
		return (0);
	return (1);
}

void	uninit(t_main *m, t_philo *philos)
{
	size_t	i;

	i = 0;
	while (i < m->count)
	{
		pthread_join(philos[i].thid, NULL);
		i++;
	}
	i = 0;
	while (i < m->count)
	{
		pthread_mutex_destroy(&philos[i].fork);
		i++;
	}
	pthread_mutex_destroy(&m->mutex);
	free(philos);
}
