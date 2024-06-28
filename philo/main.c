/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:57:06 by atorma            #+#    #+#             */
/*   Updated: 2024/06/28 14:27:43 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(t_philo *p, char **argv)
{
	int	error;

	error = 0;
	p->number = ft_atoi(argv[1], &error);
	p->time_die = ft_atoi(argv[2], &error);
	p->time_eat = ft_atoi(argv[3], &error);	
	p->time_sleep = ft_atoi(argv[4], &error);
	if (error)
		return (0);

	printf("p->number: %zu\n", p->number);
	printf("p->time_die: %zu\n", p->time_die);
	printf("p->time_eat: %zu\n", p->time_eat);
	printf("p->time_sleep: %zu\n", p->time_sleep);
	return (1);
}

int main(int argc, char **argv)
{
	t_philo	p;

	if (argc != 5)
	{
		printf("Usage: ./philo <number_philos> <die_ms> <eat_ms> <sleep_ms>\n");
		return (0);
	}
	if (!parse_args(&p, argv))
	{
		printf("Error: Invalid arguments\n");
		return (0);
	}

	return (0);
}
