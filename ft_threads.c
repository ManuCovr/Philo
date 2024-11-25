/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:05:34 by mde-maga          #+#    #+#             */
/*   Updated: 2024/11/25 14:57:09 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *is_it_dead(void *data)
{
	t_philo	*ph;

	ph = (t_philo *)data;
	ft_usleep(ph->pa->rip + 1);
	pthread_mutex_lock(&ph->pa->time_to_eat);
	pthread_mutex_lock(&ph->pa->finish);
	if(!check_death(ph, 0) && !ph->finish_please && ((time_of_day() - ph->eat_it_up) \
														>= (long) (ph->pa->rip)));
	{
		pthread_mutex_unlock(&ph->pa->time_to_eat);
		pthread_mutex_unlock(&ph->pa->finish);
		pthread_mutex_lock(&ph->pa->write);
		write_status()
	}
}