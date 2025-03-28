/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_picker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:38:31 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/28 17:15:39 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	odd_fork(t_table *ph, int num)
{
	if (num == ph->philosopher_count - 1)
	{
		pthread_mutex_lock(&(ph->forks[0]));
		pthread_mutex_lock(&(ph->forks[num]));
		if (check_life(ph))
		{
			pthread_mutex_unlock(&(ph->forks[num]));
			pthread_mutex_unlock(&(ph->forks[0]));
			return (1);
		}
	}
	else
	{
		pthread_mutex_lock(&(ph->forks[num]));
		pthread_mutex_lock(&(ph->forks[num + 1]));
		if (check_life(ph))
		{
			pthread_mutex_unlock(&(ph->forks[num + 1]));
			pthread_mutex_unlock(&(ph->forks[num]));
			return (1);
		}
	}
	return (0);
}

int	even_fork(t_table *ph, int num)
{
	if (num == ph->philosopher_count - 1)
	{
		pthread_mutex_lock(&(ph->forks[0]));
		pthread_mutex_lock(&(ph->forks[num]));
		if (check_life(ph))
		{
			pthread_mutex_unlock(&(ph->forks[0]));
			pthread_mutex_unlock(&(ph->forks[num]));
			return (1);
		}
	}
	else
	{
		pthread_mutex_lock(&(ph->forks[num]));
		pthread_mutex_lock(&(ph->forks[num + 1]));
		if (check_life(ph))
		{
			pthread_mutex_unlock(&(ph->forks[num]));
			pthread_mutex_unlock(&(ph->forks[num + 1]));
			return (1);
		}
	}
	return (0);
}
