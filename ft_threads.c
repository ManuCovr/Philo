/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:05:34 by mde-maga          #+#    #+#             */
/*   Updated: 2024/11/28 12:40:36 by mde-maga         ###   ########.fr       */
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
	if(!check_death(ph, 0) && !ph->finish_please && \
					((time_of_day() - ph->eat_it_up) >= (long) (ph->pa->rip)));
	{
		pthread_mutex_unlock(&ph->pa->time_to_eat);
		pthread_mutex_unlock(&ph->pa->finish);
		pthread_mutex_lock(&ph->pa->write);
		write_status();
		pthread_mutex_unlock(&ph->pa->write);
		check_death(ph, 1);
	}
	pthread_mutex_unlock(&ph->pa->time_to_eat);
	pthread_mutex_unlock(&ph->pa->finish);
	return (NULL);
}

void *thread(void *data)
{
	t_philo			*ph;

	ph = (t_philo *)data;
	if(ph->id % 2 == 0)
		ft_usleep(ph->pa->gluttony / 10);
	while(!check_death(ph, 0))
	{
		pthread_create(&ph->rip_id, NULL, is_it_dead, data);
		activity(ph);
		pthread_detach(ph->rip_id);
		if((int)++ph->n_eat == ph->pa->m_eat)
		{
			pthread_mutex_lock(&ph->pa->finish);
			ph->finish_please = 1;
			ph->pa->n_finish++;
			if (ph->pa->n_finish == ph->pa->total)
			{
				pthread_mutex_unlock(&ph->pa->finish);
				check_death(ph, 2);
			}
			pthread_mutex_unlock(&ph->pa->finish);
			return (NULL);
		}
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
			return (ft_exit("Pthread did not return 0\n"));
		i++;
	}
	return (1);
}