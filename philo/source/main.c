/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:57:06 by atorma            #+#    #+#             */
/*   Updated: 2024/08/14 15:47:14 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

size_t	ft_atoi(const char *s, int *error);

int	check_args(t_main *m)
{
	if (!m->count || !m->time_die || !m->time_eat || !m->time_sleep)
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
	m->meals_limit = 0;
	if (argc == 6)
	{
		m->meals_limit = ft_atoi(argv[5], &error);
		if (!m->meals_limit)
			return (0);
	}
	if (error || !check_args(m))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_main	m;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo %s",
			"<die_ms> <eat_ms> <sleep_ms>, <meal_limit>\n");
		return (EXIT_FAILURE);
	}
	if (!parse_args(&m, argc, argv))
	{
		printf("Error: Invalid arguments\n");
		return (EXIT_FAILURE);
	}
	if (!philo_run(&m))
	{
		printf("Error encountered\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
