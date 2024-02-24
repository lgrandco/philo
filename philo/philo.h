/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 23:12:51 by leo               #+#    #+#             */
/*   Updated: 2024/02/24 12:04:57 by legrandc         ###   ########.fr       */
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

# define ERR "Usage: philo_nb death_time eating_time sleeping_time [max_meals]\n"

typedef struct s_vars
{
	size_t			philo_nb;
	pthread_t		*threads;
	pthread_mutex_t	incr;
	pthread_mutex_t	write;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	*forks;
	pthread_mutex_t	m_alive;
	pthread_mutex_t	m_count;
	size_t			*last_meals;
	size_t			count;
	size_t			index;
	size_t			start_time;
	size_t			death_time;
	size_t			eating_time;
	size_t			sleeping_time;
	size_t			max_meals;
	int				finished;
	int				alive;
	int				max_meals_bool;

}					t_vars;

/* FUNCTIONS */
int					ft_atoi(const char *nptr);
#endif // !PHILO_H
