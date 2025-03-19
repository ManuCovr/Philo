/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:48:41 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/19 12:49:50 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(int argc, char **argv, t_clean *p)
{
	if ((argc == 5 || argc == 6) && numeric(argv, 0, 1))
	{
		p->arg.total = ph_atoi(argv[1]);
		p->arg.rip = ph_atoi(argv[2]);
		p->arg.gluttony = ph_atoi(argv[3]);
		p->arg.sleep = ph_atoi(argv[4]);
		p->arg.m_eat = -1;
		if (argc == 6)
			p->arg.m_eat = ph_atoi(argv[5]);
		if (p->arg.total <= 0 || p->arg.rip <= 0 || p->arg.gluttony <= 0
			|| p->arg.sleep <= 0)
			return (0);
		return (1);
	}
	return (0);
}
