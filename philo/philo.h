/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 23:12:51 by leo               #+#    #+#             */
/*   Updated: 2024/02/27 12:03:11 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define ERR "Usage: philo_nb death_time \eating_time sleeping_time [max_meals]\n"
# define MUTEX_ERR "Mutex initilization error\n"

typedef struct s_vars
{
	ssize_t			philo_nb;
	pthread_t		*threads;
	pthread_mutex_t	incr;
	pthread_mutex_t	write;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	*forks;
	pthread_mutex_t	m_alive;
	pthread_mutex_t	m_count;
	pthread_mutex_t	m_meal;
	ssize_t			*last_meals;
	ssize_t			count;
	ssize_t			index;
	ssize_t			start_time;
	ssize_t			death_time;
	ssize_t			eating_time;
	ssize_t			sleeping_time;
	ssize_t			max_meals;
	int				finished;
	int				alive;
	int				max_meals_bool;

}					t_vars;

/* FUNCTIONS */
void				init_mut(t_vars *vars);
void				free_all(t_vars *vars);
void				ft_usleep(ssize_t time);
ssize_t				time_to_ms(void);
void				exit_error(char *s, void *a, void *b, void *c);
void				*alloc_and_cpy(const void *src, ssize_t n);
int					all_alive(t_vars *vars);
int					is_dead(t_vars *vars, ssize_t ms);
int					finished_eating(t_vars *vars);
void				ft_usleep(ssize_t time);
int					eat(t_vars *vars, ssize_t num);
int					philo_sleep(t_vars *vars, ssize_t num);
int					take_forks(t_vars *vars, ssize_t num);
void				init_vars(char **av, t_vars *vars);
int					ft_atoi(const char *nptr);
ssize_t				time_to_ms(void);

#endif // !PHILO_H
