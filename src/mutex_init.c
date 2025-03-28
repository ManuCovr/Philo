/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:38:13 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/28 17:21:23 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	left_fork(t_table *ph)
{
	int	i;

	i = 0;
	while (i < ph->philosopher_count)
	{
		if (pthread_mutex_init(&(ph->forks[i]), NULL))
		{
			printf("Error initializing mutexes\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_mutexes(t_table *ph)
{
	ph->forks = (pthread_mutex_t *)malloc(
			sizeof(pthread_mutex_t) * ph->philosopher_count);
	if (!ph->forks)
		return (1);
	if (left_fork(ph))
		return (1);
	return (0);
}

static int	ft_philosopher(t_table *ph)
{
	int	i;

	i = 0;
	ph->philosophers = ft_calloc(sizeof(t_philosopher), ph->philosopher_count);
	if (!(ph->philosophers))
		return (1);
	while (i < ph->philosopher_count)
	{
		ph->philosophers[i].table = ph;
		ph->philosophers[i].id = i;
		ph->philosophers[i].meal_count = 0;
		if (pthread_mutex_init(&(ph->philosophers[i].eating_mutex), NULL))
		{
			printf("Error initializing mutexes\n");
			return (1);
		}
		if (pthread_mutex_init(&(ph->philosophers[i].writing_mutex), NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&(ph->table_mutex), NULL))
		return (1);
	return (0);
}

static int	ft_start_thread(t_table *ph)
{
	int	i;

	i = 0;
	ph->start_time = current_time();
	while (i < ph->philosopher_count)
	{
		ph->philosophers[i].last_meal_time = current_time();
		if (pthread_create(&ph->threads[i], NULL,
				&philo_life, &ph->philosophers[i]))
			return (1);
		i++;
	}
	if (pthread_create(&ph->monitor, NULL, &monitor_death, ph->philosophers))
		return (1);
	i = 0;
	while (i < ph->philosopher_count)
	{
		pthread_join(ph->threads[i], NULL);
		i++;
	}
	pthread_join(ph->monitor, NULL);
	return (0);
}

int	init(t_table *ph)
{
	ph->threads = (pthread_t *)ft_calloc(
			sizeof(pthread_t), ph->philosopher_count);
	if (!(ph->threads))
	{
		free(ph->threads);
		return (1);
	}
	if (ft_philosopher(ph))
	{
		free(ph->philosophers);
		printf("Error trying to sit down the philosophers\n");
		return (1);
	}
	if (ft_start_thread(ph))
	{
		printf("Thread Error\n");
		return (1);
	}
	return (0);
}
