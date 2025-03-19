/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:12:21 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/19 12:42:40 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_exit(char *str)
{
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd(str, 2);
	return (0);
}

int	check_death2(t_clean *p)
{
	pthread_mutex_lock(&p->arg.killed);
	if (p->arg.enough)
	{
		pthread_mutex_unlock(&p->arg.killed);
		return (1);
	}
	pthread_mutex_unlock(&p->arg.killed);
	return (0);
}

void	stop(t_clean *p)
{
	int	i;

	i = -1;
	while (!check_death2(p))
		usleep(100);
	while (++i < p->arg.total)
		pthread_join(p->ph[i].thread_id, NULL);
	pthread_mutex_destroy(&p->arg.write);
	pthread_mutex_destroy(&p->arg.killed);
	pthread_mutex_destroy(&p->arg.time_to_eat);
	pthread_mutex_destroy(&p->arg.finish);
	i = -1;
	while (++i < p->arg.total)
		pthread_mutex_destroy(&p->ph[i].l_fork);
	if (p->arg.enough == 2)
		printf("Nice! Each philosopher ate %d time(s) :)\n", p->arg.m_eat);
	free(p->ph);
}

int	main(int ac, char **av)
{
	t_clean	p;

	if (!(parse_args(ac, av, &p)))
		return (ft_exit("Invalid Arguments\n"));
	p.ph = malloc(sizeof(t_philo) * p.arg.total);
	if (!p.ph)
		return (ft_exit("Malloc returned NULL\n"));
	if (!initialize(&p) || !threading(&p))
	{
		free(p.ph);
		return (0);
	}
	stop(&p);
}
