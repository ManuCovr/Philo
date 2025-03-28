/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:38:19 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/28 17:23:53 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_status(t_philosopher *philosophers, int philo_nb, char *flag)
{
	pthread_mutex_lock(&(philosophers->writing_mutex));
	printf("%d %d %s\n", (current_time()
			- philosophers->table->start_time), philo_nb + 1, flag);
	pthread_mutex_unlock(&(philosophers->writing_mutex));
}

static int	philo_ate(t_table *ph, t_philosopher *philosophers)
{
	int	i;

	if (ph->philosopher_count == 1)
	{
		ft_usleep(ph->time_to_die, ph);
		return (1);
	}
	pthread_mutex_lock(&(ph->table_mutex));
	if ((ph->required_meals > 0) && (
			philosophers->meal_count >= ph->required_meals))
		ph->full_count++;
	pthread_mutex_unlock(&(ph->table_mutex));
	pthread_mutex_lock(&(ph->table_mutex));
	if ((current_time() - philosophers->last_meal_time) >= ph->time_to_die)
		ph->dead = 1;
	i = ph->dead;
	pthread_mutex_unlock(&(ph->table_mutex));
	return (i);
}

void	ft_usleep(int start_time, t_table *ph)
{
	long int	st;

	st = current_time();
	while (current_time() < start_time + st)
	{
		pthread_mutex_lock(&(ph->table_mutex));
		if (ph->dead)
		{
			pthread_mutex_unlock(&(ph->table_mutex));
			break ;
		}
		pthread_mutex_unlock(&(ph->table_mutex));
		usleep(100);
	}
}

static int	check_full(t_table *ph)
{
	if (ph->full_count >= ph->philosopher_count)
	{
		pthread_mutex_lock(&(ph->table_mutex));
		ph->dead = 1;
		pthread_mutex_unlock(&(ph->table_mutex));
		return (1);
	}
	return (0);
}

void	*monitor_death(void *arg)
{
	t_philosopher			*philosophers;
	t_table					*ph;
	int						i;

	philosophers = (t_philosopher *)arg;
	ph = philosophers->table;
	while (1)
	{
		i = 0;
		pthread_mutex_lock(&(ph->table_mutex));
		ph->full_count = 0;
		pthread_mutex_unlock(&(ph->table_mutex));
		while (i < ph->philosopher_count)
		{
			if (philo_ate(ph, &(philosophers[i])))
			{
				print_status(philosophers, i, "is dead");
				return (NULL);
			}
			i++;
		}
		if (check_full(ph))
			return (NULL);
	}
}
