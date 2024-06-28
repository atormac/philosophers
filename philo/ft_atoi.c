/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:34:18 by atorma            #+#    #+#             */
/*   Updated: 2024/06/28 14:32:21 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_valid(const char *s)
{
	if (*s == '\0')
		return (0);
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
}

size_t	ft_atoi(const char *s, int *error)
{
	size_t		res;

	res = 0;
	if (*error == 1)
		return (0);
	if (!is_valid(s))
	{
		*error = 1;
		return (0);
	}
	while (*s && *s >= '0' && *s <= '9')
	{
		res = res * 10 + (*s - '0');
		s++;
	}
	return (res);
}
