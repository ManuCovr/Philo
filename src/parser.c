/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:37:53 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/28 17:10:36 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

unsigned int	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	save_args(t_table *ph, char **av)
{
	ph->dead = 0;
	ph->philosopher_count = string_to_long(av[1]);
	ph->time_to_die = string_to_long(av[2]);
	ph->time_to_eat = string_to_long(av[3]);
	ph->time_to_sleep = string_to_long(av[4]);
	if (av[5])
		ph->required_meals = string_to_long(av[5]);
	else
		ph->required_meals = -1;
}

int	parse_args(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (is_invalid_arg(av[i]))
			return (1);
		if (string_to_long(av[i]) <= 0 || string_to_long(av[i]) > INT_MAX)
			return (1);
		i++;
	}
	return (0);
}
