/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:12:19 by mde-maga          #+#    #+#             */
/*   Updated: 2024/12/02 16:59:48 by mde-maga         ###   ########.fr       */
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

typedef struct s_stats
{
	int						total;
	int						rip; // die
	int						gluttony; // eat
	int						sleep;
	int						m_eat;
	long int				start_t;
	pthread_mutex_t			write; // write_mutex
	pthread_mutex_t			killed; // dead
	pthread_mutex_t			time_to_eat; // time_eat
	pthread_mutex_t			finish;
	int						n_finish; // nb_p_finish
	int						enough; // stop
}							t_stats;

typedef struct s_philo
{
	int						id;
	pthread_t				thread_id;
	pthread_t				rip_id; // thread_death_id;
	pthread_mutex_t			*r_fork;
	pthread_mutex_t			l_fork;
	t_stats					*pa;
	long int				eat_it_up; // ms_eat
	unsigned int			n_eat; // nb_eat
	int						finish_please;
}							t_philo;

typedef struct s_clean
{
	t_philo					*ph;
	t_stats					arg; // a
}							t_clean;


int			main(int ac, char **av);
int			ft_exit(char *str);
int			check_death2(t_clean *p);
void		stop(t_clean *p);

int			ph_atoi(const char *str);
void		init(t_clean *p);
int			numeric(char **argv, int i, int j);
int			initialize(t_clean *p);

int			check_death(t_philo *ph, int i);
long int	time_of_day(void);
void 		ft_usleep(long int time_in_ms);
int			parse_args(int argc, char **argv, t_clean *p);

int			threading(t_clean *p);
void		*monitor(void *data);
void		*philosopher_routine(void *data);

void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
int			ft_strlen(char *str);

void		activity(t_philo *ph);
void		sleep_think(t_philo *ph);
void		write_status(char *str, t_philo *ph);


#endif