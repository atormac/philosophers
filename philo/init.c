
#include "philo.h"
#include <string.h>

int	init(t_philo *philos, t_philo *p, t_main *m)
{
	size_t	i;

	i = 0;
	if (pthread_mutex_init(&m->mutex, NULL) != 0)
		return (0);
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
	while (i < m->count)
	{
		philos[i].mutex = &m->mutex;
		philos[i].fork_left = &philos[i].fork;
		philos[i].fork_right = &philos[(i + 1) % m->count].fork;
		printf("philo: %zu, fork_left: %p, fork_right: %p\n",
				philos[i].number, philos[i].fork_left, philos[i].fork_right);
		i++;
	}
	return (1);
}

void	uninit(t_main *m, t_philo *philos)
{
	size_t	i;

	i = 0;
	while (i < m->count)
	{
		pthread_mutex_destroy(&philos[i].fork);
		i++;
	}
	pthread_mutex_destroy(&m->mutex);
	free(philos);
}
