/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:26:29 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/28 17:27:39 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_life(t_table *ph)
{
	if (ph->philosopher_count == 1)
	{
		ft_usleep(ph->time_to_die, ph);
		return (1);
	}
	pthread_mutex_lock(&(ph->table_mutex));
	if (ph->dead)
	{
		pthread_mutex_unlock(&(ph->table_mutex));
		return (1);
	}
	if (ph->full_count >= ph->philosopher_count)
	{
		pthread_mutex_unlock(&(ph->table_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(ph->table_mutex));
	return (0);
}

int	forking(t_table *ph, int num)
{
	if (ph->philosopher_count % 2 == 1)
	{
		if (odd_fork(ph, num))
			return (0);
	}
	else
	{
		if (even_fork(ph, num))
			return (0);
	}
	return (1);
}
