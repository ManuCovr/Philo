/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:39:01 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/08 11:09:28 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	check_death(t_philo *ph, int i)
{
	pthread_mutex_lock(&ph->pa->killed);
	if (i)
		ph->pa->enough = i;
	if (ph->pa->enough)
	{
		pthread_mutex_unlock(&ph->pa->killed);
		return (1);
	}
	pthread_mutex_unlock(&ph->pa->killed);
	return (0);
}

long int time_of_day(void)
{
    long int time;
    struct timeval current_time;

    time = 0;
    if (gettimeofday(&current_time, NULL) == -1)
        ft_exit("gettimeofday returned -1\n");
    time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000); // milliseconds
    return time;
}

void ft_usleep(long int time_in_ms)
{
    long int start_time = time_of_day();

    // Sleep in small chunks (e.g., 1ms) to avoid busy-waiting and check time progress
    while ((time_of_day() - start_time) < time_in_ms)
    {
        usleep(1000);  // Sleep for 1ms at a time
    }
}