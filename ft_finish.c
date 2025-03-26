/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_finish.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 00:21:55 by joafaust          #+#    #+#             */
/*   Updated: 2025/03/26 12:42:29 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_deaths(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philos)
	{
		pthread_mutex_lock(&sim->meal_check);
		if (get_time_in_ms()
			- sim->philos[i].last_meal_time >= sim->time_to_die)
		{
			pthread_mutex_unlock(&sim->meal_check);
			print_action(sim, sim->philos[i].id, "died");
			pthread_mutex_lock(&sim->death_check);
			sim->stop = 1;
			pthread_mutex_unlock(&sim->death_check);
			return ;
		}
		pthread_mutex_unlock(&sim->meal_check);
		i++;
	}
}

void	check_all_eaten(t_simulation *sim)
{
	int	i;
	int	finished_philos;

	i = 0;
	finished_philos = 0;
	while (i < sim->num_philos)
	{
		if (has_eaten_enough(&sim->philos[i]))
			finished_philos++;
		i++;
	}
	if (finished_philos == sim->num_philos)
		sim->stop = 1;
}
