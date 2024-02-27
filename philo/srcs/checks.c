/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:45:10 by legrandc          #+#    #+#             */
/*   Updated: 2024/02/27 11:56:56 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	finished_eating(t_vars *vars)
{
	int	ret;

	pthread_mutex_lock(&vars->m_count);
	if (vars->max_meals_bool && (vars->count == vars->philo_nb
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
	ssize_t	*last_meals_cpy;

	i = 0;
	pthread_mutex_lock(&vars->m_meal);
	last_meals_cpy = alloc_and_cpy(vars->last_meals, vars->philo_nb
			* sizeof(*vars->last_meals));
	pthread_mutex_unlock(&vars->m_meal);
	if (!last_meals_cpy)
		return (-1);
	while (i < vars->philo_nb)
	{
		if (ms - last_meals_cpy[i] > vars->death_time)
		{
			printf("%ld %ld %s\n", vars->last_meals[i] + vars->death_time
				- vars->start_time, i + 1, "died");
			pthread_mutex_lock(&vars->m_alive);
			vars->alive = 0;
			pthread_mutex_unlock(&vars->m_alive);
			return (free(last_meals_cpy), 1);
		}
		i++;
	}
	return (free(last_meals_cpy), 0);
}

int	all_alive(t_vars *vars)
{
	int	ret;

	pthread_mutex_lock(&vars->m_alive);
	ret = vars->alive;
	pthread_mutex_unlock(&vars->m_alive);
	return (ret);
}
