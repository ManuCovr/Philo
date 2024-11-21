/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:42:06 by mde-maga          #+#    #+#             */
/*   Updated: 2024/11/18 12:25:47 by mde-maga         ###   ########.fr       */
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

int	numeric(char **argv, int i, int j)
{
	while (argv[j])
	{
		while (argv[j][i])
		{
			if (argv[j][i] < '0' || argv[j][i] > '9' || ft_strlen(argv[j]) > 10)
				return (0);
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}


void	init_threads(t_clean *p)
{
	pthread_mutex_init(&p->arg.write, NULL);
	pthread_mutex_init(&p->arg.killed, NULL);
	pthread_mutex_init(&p->arg.time_to_eat, NULL);
	pthread_mutex_init(&p->arg.finish, NULL);
}

int	initialize(t_clean *p)
{
	int	i;

	i = 0;
	p->arg.start_t = actual_time();
	p->arg.enough = 0;
	p->arg.n_finish = 0;
	init_threads(p);
	while (i < p->arg.total)
	{
		p->ph[i].id = i + 1;
		p->ph[i].eat_it_up = p->arg.start_t;
		p->ph[i].n_eat = 0;
		p->ph[i].finish_please = 0;
		p->ph[i].r_fork = NULL;
		pthread_mutex_init(&p->ph[i].l_fork, NULL);
		if (p->arg.total == 1)
			return (1);
		if (i == p->arg.total - 1)
			p->ph[i].r_fork = &p->ph[0].l_fork;
		else
			p->ph[i].r_fork = &p->ph[i + 1].l_fork;
		i++;
	}
	return (1);
}