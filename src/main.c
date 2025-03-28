/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:38:27 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/28 17:10:21 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	ft_clean(t_table *ph)
{
	int	i;

	i = 0;
	while (i < ph->philosopher_count)
	{
		pthread_mutex_destroy(&(ph->forks[i]));
		pthread_mutex_destroy(&(ph->philosophers[i].eating_mutex));
		pthread_mutex_destroy(&(ph->philosophers[i].writing_mutex));
		i++;
	}
	pthread_mutex_destroy(&(ph->table_mutex));
	free(ph->philosophers);
	free(ph->forks);
	free(ph->threads);
	free(ph);
}

static int	ft_start(t_table *ph)
{
	if (init_mutexes(ph))
	{
		free(ph->forks);
		return (1);
	}
	if (init(ph))
	{
		ft_clean(ph);
		return (1);
	}
	else
		ft_clean(ph);
	return (0);
}

int	main(int ac, char **av)
{
	t_table	*ph;

	ph = (t_table *)ft_calloc(sizeof(t_table), 1);
	if (!ph)
		return (1);
	if (ac != 5 && ac != 6)
	{
		printf("Error w/ arg num\n");
		free(ph);
		return (1);
	}
	if (parse_args(av))
	{
		printf("Args incorrect\n");
		free(ph);
		return (1);
	}
	save_args(ph, av);
	if (ft_start(ph))
		return (1);
	return (0);
}
