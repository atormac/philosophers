/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:57:06 by atorma            #+#    #+#             */
/*   Updated: 2024/07/29 16:53:34 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(t_philo *p)
{
	if (!p->number || !p->time_die || !p->time_eat || !p->time_sleep)
		return (0);
	if (p->number > 200)
		return (0);
	return (1);
}

int	parse_args(t_philo *p, int argc, char **argv)
{
	int	error;

	error = 0;
	p->number = ft_atoi(argv[1], &error);
	p->time_die = ft_atoi(argv[2], &error);
	p->time_eat = ft_atoi(argv[3], &error);	
	p->time_sleep = ft_atoi(argv[4], &error);
	p->is_opt = 0;
	p->count_eat = 1;
	if (argc == 6)
	{
		p->count_eat = ft_atoi(argv[5], &error);
		p->is_opt = 1;
	}
	if (error)
		return (0);
	if (!check_args(p))
		return (0);
	printf("p->number: %zu\n", p->number);
	printf("p->time_die: %zu\n", p->time_die);
	printf("p->time_eat: %zu\n", p->time_eat);
	printf("p->time_sleep: %zu\n", p->time_sleep);
	printf("p->eat_count: %zu\n", p->count_eat);
	p->fork_count = p->number - 1;
	if (p->fork_count == 0)
		p->fork_count = 1;
	return (1);
}

int main(int argc, char **argv)
{
	t_philo	p;
	pthread_mutex_t	mutex;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo <number_philos> <die_ms> <eat_ms> <sleep_ms>, <opt_eat_count>\n");
		return (0);
	}
	if (!parse_args(&p, argc, argv))
	{
		printf("Error: Invalid arguments\n");
		return (0);
	}
	p.mutex = &mutex;
	philo_threads_create(&p);
	printf("Finished...\n");
	return (0);
}
