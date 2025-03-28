/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:18:30 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/28 17:27:45 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* ========================== HEADER FILES ========================== */
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <time.h>
# include <sys/time.h>

/* ========================== STRUCTS ========================== */
typedef struct s_philosopher	t_philosopher;
typedef struct s_table			t_table;

typedef struct s_philosopher
{
	int				id;
	int				meal_count;
	unsigned int	last_meal_time;
	pthread_mutex_t	eating_mutex;
	pthread_mutex_t	writing_mutex;
	t_table			*table;
}				t_philosopher;

typedef struct s_table
{
	pthread_t		*threads;
	pthread_t		monitor;
	int				dead;
	int				philosopher_count;
	int				full_count;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				required_meals;
	unsigned int	start_time;
	pthread_mutex_t	table_mutex;
	pthread_mutex_t	*forks;
	t_philosopher	*philosophers;
}			t_table;

/* ========================== FUNCTION PROTOTYPES ========================== */
/* --------------------- MAIN & ARGUMENT HANDLING --------------------- */
int				main(int ac, char **av);
long			string_to_long(const char *s);
int				is_invalid_arg(char *str);
int				parse_args(char **av);
void			save_args(t_table *table, char **av);

/* --------------------- MEMORY, TIME & INITIALIZATION --------------------- */
unsigned int	current_time(void);
void			*ft_calloc(size_t nmemb, size_t size);
int				init_mutexes(t_table *table);
int				init(t_table *table);

/* --------------------- THREAD ROUTINES & ACTIONS --------------------- */
void			*philo_life(void *arg);
void			*monitor_death(void *arg);
void			print_status(t_philosopher *philosophers, int id, char *status);
void			ft_usleep(int start_time, t_table *table);
int				odd_fork(t_table *table, int num);
int				even_fork(t_table *table, int num);
int				check_life(t_table *table);
int				forking(t_table *ph, int num);

#endif