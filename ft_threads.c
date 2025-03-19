/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:05:34 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/19 12:45:51 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*is_it_dead(void *data)
{
	t_philo	*ph;

	ph = (t_philo *)data;
	while (!check_death(ph, 0))
	{
		pthread_mutex_lock(&ph->pa->time_to_eat);
		if (!ph->finish_please && (time_of_day()
				- ph->eat_it_up >= ph->pa->rip))
		{
			pthread_mutex_unlock(&ph->pa->time_to_eat);
			pthread_mutex_lock(&ph->pa->write);
			write_status("died :(\n", ph);
			pthread_mutex_unlock(&ph->pa->write);
			check_death(ph, 1);
			break ;
		}
		pthread_mutex_unlock(&ph->pa->time_to_eat);
		ft_usleep(1);
	}
	return (NULL);
}

void	*thread(void *data)
{
	t_philo	*ph;

	ph = (t_philo *)data;
	if (ph->id % 2 == 0)
		ft_usleep(ph->pa->gluttony / 10);
	pthread_create(&ph->rip_id, NULL, is_it_dead, data);
	pthread_detach(ph->rip_id);
	while (!check_death(ph, 0))
	{
		activity(ph);
		pthread_mutex_lock(&ph->pa->finish);
		if ((int)++ph->n_eat == ph->pa->m_eat)
		{
			ph->finish_please = 1;
			ph->pa->n_finish++;
			if (ph->pa->n_finish == ph->pa->total)
			{
				pthread_mutex_unlock(&ph->pa->finish);
				check_death(ph, 2);
				break ;
			}
		}
		pthread_mutex_unlock(&ph->pa->finish);
	}
	return (NULL);
}

int	threading(t_clean *p)
{
	int	i;

	i = 0;
	while (i < p->arg.total)
	{
		p->ph[i].pa = &p->arg;
		if (pthread_create(&p->ph[i].thread_id, NULL, thread, &p->ph[i]) != 0)
			return (ft_exit("Pthread did not return (0\n"));
		i++;
	}
	return (1);
}
