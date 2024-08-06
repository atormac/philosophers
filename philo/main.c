/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:57:06 by atorma            #+#    #+#             */
/*   Updated: 2024/07/31 14:41:07 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(t_main *p)
{
	if (p->count <= 0 || !p->time_die || !p->time_eat || !p->time_sleep)
		return (0);
	return (1);
}

int	parse_args(t_main *m, int argc, char **argv)
{
	int	error;

	error = 0;
	m->count = ft_atoi(argv[1], &error);
	m->time_die = ft_atoi(argv[2], &error);
	m->time_eat = ft_atoi(argv[3], &error);	
	m->time_sleep = ft_atoi(argv[4], &error);
	m->eat_count = -1;
	if (argc == 6)
		m->eat_count = ft_atoi(argv[5], &error);
	if (error)
		return (0);
	if (!check_args(m))
		return (0);
	printf("main->count: %zu\n", m->count);
	printf("main->time_die: %zu\n", m->time_die);
	printf("main->time_eat: %zu\n", m->time_eat);
	printf("main->time_sleep: %zu\n", m->time_sleep);
	printf("main->eat_count: %zu\n", m->eat_count);
	return (1);
}

void	print_message(int num, int state);

int main(int argc, char **argv)
{
	t_main	m;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo <number_philos> <die_ms> <eat_ms> <sleep_ms>, <opt_eat_count>\n");
		return (EXIT_FAILURE);
	}
	if (!parse_args(&m, argc, argv))
	{
		printf("Error: Invalid arguments\n");
		return (EXIT_FAILURE);
	}
	if (!philo_run(&m))
	{
		printf("Error\n");
		return (EXIT_FAILURE);
	}
	printf("Finished...\n");
	return (0);
}
