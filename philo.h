/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:12:19 by mde-maga          #+#    #+#             */
/*   Updated: 2024/11/14 12:14:03 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <stdbool.h>

typedef struct	s_philo
{
	int						id;
	int						enough;
	long int				gluttony;
	unsigned int			n_eat;
	pthread_t				t_id;
	pthread_t				t_rip_id;
	pthread_mutex_t			*r_fork;
	pthread_mutex_t			l_fork;
	t_stats					*p;
}							t_philo;

typedef struct	s_stats
{
	int						total;
	int						rip;
	int						eat;
	int						sleep;
	int						last_meal;
	int						n_finsh;
	int						stop;
	long int				start;
	pthread_mutex_t			write;
	pthread_mutex_t			death;
	pthread_mutex_t			meal;
	pthread_mutex_t			finish;
}							t_stats;

typedef struct s_clean
{
	t_philo					*philo;
	t_stats					stats;
}							t_clean;


int		karen(int flag);
int		error_syntax(char *str);
int		main(int ac, char **av);



#endif