/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:42:06 by mde-maga          #+#    #+#             */
/*   Updated: 2024/11/14 14:13:15 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	ph_atoi(const char *str)
{
	int		i;
	long	sum;

	sum = 0;
	i = -1;
	while (str[++i])
		sum = (sum * 10) + (str[i] - 48);
	return (sum);
}

void init_threads(t_clean *philo)
{
	pthread_mutex_init(&philo->stats.write, NULL);
	pthread_mutex_init(&philo->stats.death, NULL);
	pthread_mutex_init(&philo->stats.meal, NULL);
	pthread_mutex_init(&philo->stats.finish, NULL);
}