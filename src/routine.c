/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:37:46 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/28 17:27:28 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	lock_forks(t_table *ph, int num, int flag)
{
	if (flag == 0)
	{
		if (forking(ph, num))
		{
			print_status(ph->philosophers, num, "has taken a fork");
			print_status(ph->philosophers, num, "has taken a fork");
		}
		else
			return (0);
	}
	else
	{
		if (num == ph->philosopher_count - 1)
			pthread_mutex_unlock(&(ph->forks[0]));
		else
			pthread_mutex_unlock(&(ph->forks[num + 1]));
		pthread_mutex_unlock(&(ph->forks[num]));
	}
	return (1);
}

static int	eat(t_table *ph, t_philosopher *philosophers)
{
	if (lock_forks(ph, philosophers->id, 0))
	{
		pthread_mutex_lock(&(ph->table_mutex));
		philosophers->last_meal_time = current_time();
		print_status(ph->philosophers, philosophers->id, "is eating");
		pthread_mutex_unlock(&(ph->table_mutex));
		ft_usleep(ph->time_to_eat, ph);
		pthread_mutex_lock(&(ph->table_mutex));
		philosophers->meal_count++;
		pthread_mutex_unlock(&(ph->table_mutex));
		lock_forks(ph, philosophers->id, 1);
	}
	else
		return (1);
	return (0);
}

static void	pre_cycle_delay(t_philosopher *philo, t_table *table)
{
	if (philo->id % 2 == 1 && table->philosopher_count % 2 == 1)
		ft_usleep(table->time_to_eat * 2 - table->time_to_sleep, table);
	else if (philo->id % 2 == 1)
		ft_usleep(table->time_to_eat - table->time_to_sleep, table);
}

static int	philo_cycle(t_philosopher *philo, t_table *table)
{
	if (check_life(table))
		return (1);
	if (eat(table, philo))
		return (1);
	if (check_life(table))
		return (1);
	print_status(philo, philo->id, "is sleeping");
	ft_usleep(table->time_to_sleep, table);
	if (check_life(table))
		return (1);
	print_status(philo, philo->id, "is thinking");
	if (check_life(table))
		return (1);
	if ((table->philosopher_count % 2 == 1) && (
			2 * table->time_to_eat > table->time_to_sleep))
		ft_usleep((2 * table->time_to_eat - table->time_to_sleep), table);
	else if ((table->philosopher_count % 2 == 0) && (
			table->time_to_eat > table->time_to_sleep))
		ft_usleep((table->time_to_eat - table->time_to_sleep), table);
	return (0);
}

void	*philo_life(void *arg)
{
	t_philosopher	*philo;
	t_table			*table;

	philo = (t_philosopher *)arg;
	table = philo->table;
	pre_cycle_delay(philo, table);
	while (1)
	{
		if (philo_cycle(philo, table))
			return (NULL);
	}
	return (NULL);
}
