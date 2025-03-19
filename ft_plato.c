/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plato.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:03:17 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/19 12:46:24 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(char *str, t_philo *ph)
{
	long int	time;

	time = -1;
	time = time_of_day() - ph->pa->start_t;
	if (time >= 0 && time <= 2147483647 && !check_death(ph, 0))
	{
		printf("%ld ", time);
		printf("Philo %d %s", ph->id, str);
	}
}

void	sleep_think(t_philo *ph)
{
	pthread_mutex_lock(&ph->pa->write);
	write_status("is sleeping\n", ph);
	pthread_mutex_unlock(&ph->pa->write);
	ft_usleep(ph->pa->sleep);
	pthread_mutex_lock(&ph->pa->write);
	write_status("is thinking\n", ph);
	pthread_mutex_unlock(&ph->pa->write);
}

void	activity(t_philo *ph)
{
	pthread_mutex_lock(&ph->l_fork);
	pthread_mutex_lock(&ph->pa->write);
	write_status("has taken a fork\n", ph);
	pthread_mutex_unlock(&ph->pa->write);
	if (!ph->r_fork)
	{
		ft_usleep(ph->pa->rip * 2);
		return ;
	}
	pthread_mutex_lock(ph->r_fork);
	pthread_mutex_lock(&ph->pa->write);
	write_status("has taken a fork\n", ph);
	pthread_mutex_unlock(&ph->pa->write);
	pthread_mutex_lock(&ph->pa->write);
	write_status("is eating\n", ph);
	pthread_mutex_lock(&ph->pa->time_to_eat);
	ph->eat_it_up = time_of_day();
	pthread_mutex_unlock(&ph->pa->time_to_eat);
	pthread_mutex_unlock(&ph->pa->write);
	ft_usleep(ph->pa->gluttony);
	pthread_mutex_unlock(ph->r_fork);
	pthread_mutex_unlock(&ph->l_fork);
	sleep_think(ph);
}
