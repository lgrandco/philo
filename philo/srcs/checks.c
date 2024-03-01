/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:45:10 by legrandc          #+#    #+#             */
/*   Updated: 2024/02/28 06:05:39 by legrandc         ###   ########.fr       */
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
	ssize_t	*last_meals_cpy;

	i = 0;
	if (!all_alive(vars))
		return (0);
	if (alloc_and_cpy((void **)&last_meals_cpy, vars, vars->philo_nb
			* sizeof(*vars->last_meals)) == -1)
		return (-1);
	while (++i < vars->philo_nb + 1)
	{
		if (ms - last_meals_cpy[i - 1] > vars->death_time)
		{
			printf("4\n");
			pthread_mutex_lock(&vars->m_alive);
			vars->alive = 0;
			pthread_mutex_unlock(&vars->m_alive);
			pthread_mutex_lock(&vars->write);
			printf("%ld %ld %s\n", time_to_ms() - vars->start_time, i, "died");
			pthread_mutex_unlock(&vars->write);
			return (free(last_meals_cpy), 1);
		}
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

void	check_deaths(t_vars *vars)
{
	while (all_alive(vars) || !finished_eating(vars))
	{
		if (is_dead(vars, time_to_ms()))
			return ;
		usleep(1000);
	}
}
