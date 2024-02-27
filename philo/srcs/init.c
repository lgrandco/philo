/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 08:16:55 by legrandc          #+#    #+#             */
/*   Updated: 2024/02/27 12:03:45 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mut(t_vars *vars)
{
	ssize_t	i;

	i = 0;
	while (i < vars->philo_nb)
	{
		vars->last_meals[i] = time_to_ms();
		if (pthread_mutex_init(&vars->forks[i], NULL) != 0)
			exit_error(MUTEX_ERR, vars->threads, vars->last_meals,
				vars->threads);
		i++;
	}
	if (pthread_mutex_init(&vars->m_meal, NULL) != 0
		|| pthread_mutex_init(&vars->m_alive, NULL) != 0
		|| pthread_mutex_init(&vars->m_count, NULL) != 0
		|| pthread_mutex_init(&vars->write, NULL) != 0
		|| pthread_mutex_init(&vars->dead_lock, NULL) != 0
		|| pthread_mutex_init(&vars->incr, NULL) != 0)
		exit_error(MUTEX_ERR, vars->threads, vars->last_meals, vars->forks);
}

void	init_vars(char **av, t_vars *vars)
{
	vars->max_meals = 1;
	vars->start_time = time_to_ms();
	vars->philo_nb = ft_atoi(av[1]);
	vars->death_time = ft_atoi(av[2]);
	vars->eating_time = ft_atoi(av[3]);
	vars->sleeping_time = ft_atoi(av[4]);
	vars->max_meals_bool = (av[5] != NULL);
	if (vars->max_meals_bool)
		vars->max_meals = ft_atoi(av[5]);
	if (vars->philo_nb < 1 || vars->death_time < 1 || vars->eating_time < 1
		|| vars->sleeping_time < 1 || vars->max_meals < 1)
		exit_error("Incorrect argument\n" ERR, NULL, NULL, NULL);
	vars->index = 0;
	vars->alive = 1;
	vars->count = 0;
	vars->finished = 0;
	vars->threads = malloc(sizeof(pthread_t) * vars->philo_nb);
	if (!vars->threads)
		exit_error("Malloc error\n", NULL, NULL, NULL);
	vars->last_meals = malloc(sizeof(*vars->last_meals) * vars->philo_nb);
	if (!vars->last_meals)
		exit_error("Malloc error\n", vars->threads, NULL, NULL);
	vars->forks = malloc(sizeof(pthread_mutex_t) * vars->philo_nb);
	if (!vars->forks)
		exit_error("Malloc error\n", vars->threads, vars->last_meals, NULL);
}
