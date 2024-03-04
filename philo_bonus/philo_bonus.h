/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 23:12:51 by leo               #+#    #+#             */
/*   Updated: 2024/03/04 07:19:19 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define ERR "Usage: philo_nb death_time eating_time sleeping_time [max_meals]\n"
# define MUTEX_ERR "Mutex initilization error\n"
# define FORKS_FILE "/forks"
# define MEALS "/meals"
# define FINISHED_FILE "/finished_file"

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
	ssize_t			last_meals;
	ssize_t			count;
	ssize_t			index;
	ssize_t			start_time;
	ssize_t			death_time;
	ssize_t			eating_time;
	ssize_t			sleeping_time;
	ssize_t			max_meals;
	size_t			philo_index;
	int				finished;
	int				alive;
	int				max_meals_bool;
	sem_t			*sem_forks;
	sem_t			*sem_ongoing;
	ssize_t			*pids;

}					t_vars;

/* FUNCTIONS */
void				init_sem(t_vars *vars);
void				free_all(t_vars *vars);
void				ft_usleep(t_vars *vars, ssize_t time);
ssize_t				time_to_ms(void);
void				exit_error(char *s, void **t);
void				*alloc_and_cpy(const void *src, ssize_t n);
int					all_alive(t_vars *vars);
int					is_dead(t_vars *vars, ssize_t ms);
int					finished_eating(t_vars *vars);
int					eat(t_vars *vars, ssize_t num);
int					philo_sleep(t_vars *vars, ssize_t num);
int					take_forks(t_vars *vars, ssize_t num);
void				init_vars(char **av, t_vars *vars);
int					ft_atoi(const char *nptr);
ssize_t				time_to_ms(void);

#endif // !PHILO_BONUS_H
