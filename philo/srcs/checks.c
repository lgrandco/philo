/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:45:10 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/02 20:29:11 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	finished_eating(t_vars *vars)
{
	int	ret;

	pthread_mutex_lock(&vars->m_count);
	if (vars->max_meals_bool && (vars->count >= vars->philo_nb
			* vars->max_meals))
		ret = 1;
	else
		ret = 0;
	pthread_mutex_unlock(&vars->m_count);
	return (ret);
}

int	is_dead(t_vars *vars, ssize_t ms)
{
	ssize_t	i;
	ssize_t	test;

	i = 0;
	if (!all_alive(vars))
		return (1);
	while (++i < vars->philo_nb + 1)
	{
		pthread_mutex_lock(&vars->m_meal);
		test = vars->last_meals[i - 1];
		pthread_mutex_unlock(&vars->m_meal);
		if (ms - test > vars->death_time)
		{
			pthread_mutex_lock(&vars->m_alive);
			vars->alive = 0;
			pthread_mutex_unlock(&vars->m_alive);
			pthread_mutex_lock(&vars->write);
			printf("%ld %ld %s\n", time_to_ms() - vars->start_time, i, "died");
			pthread_mutex_unlock(&vars->write);
			return (1);
		}
	}
	return (0);
}

int	all_alive(t_vars *vars)
{
	int	ret;

	pthread_mutex_lock(&vars->m_alive);
	ret = vars->alive;
	pthread_mutex_unlock(&vars->m_alive);
	return (ret);
}

void	check_deaths(t_vars *vars)
{
	while (all_alive(vars) || !finished_eating(vars))
	{
		if (is_dead(vars, time_to_ms()) || finished_eating(vars))
			return ;
		usleep(500);
	}
}
