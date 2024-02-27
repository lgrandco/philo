/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:20:06 by legrandc          #+#    #+#             */
/*   Updated: 2024/02/27 11:56:56 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_print(t_vars *vars, long index, char *msg)
{
	pthread_mutex_lock(&vars->write);
	if (all_alive(vars) && !finished_eating(vars) && !is_dead(vars,
			time_to_ms()))
		printf("%ld %ld %s\n", time_to_ms() - vars->start_time, index + 1, msg);
	pthread_mutex_unlock(&vars->write);
}

int	take_forks(t_vars *vars, ssize_t num)
{
	if (vars->philo_nb == 1)
	{
		lock_print(vars, num, "has taken a fork");
		if (all_alive(vars))
			ft_usleep(vars->death_time);
		return (0);
	}
	if ((num + 1) % 2 == 0)
	{
		pthread_mutex_lock(&vars->forks[(num + 1) % vars->philo_nb]);
		lock_print(vars, num, "has taken a fork");
		pthread_mutex_lock(&vars->forks[num]);
		lock_print(vars, num, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&vars->forks[num]);
		lock_print(vars, num, "has taken a fork");
		pthread_mutex_lock(&vars->forks[(num + 1) % vars->philo_nb]);
		lock_print(vars, num, "has taken a fork");
	}
	return (0);
}

int	eat(t_vars *vars, ssize_t num)
{
	if (vars->philo_nb == 1)
		return (0);
	pthread_mutex_lock(&vars->m_meal);
	vars->last_meals[num] = time_to_ms();
	pthread_mutex_unlock(&vars->m_meal);
	lock_print(vars, num, "is eating");
	pthread_mutex_lock(&vars->m_count);
	vars->count++;
	pthread_mutex_unlock(&vars->m_count);
	ft_usleep(vars->eating_time);
	pthread_mutex_unlock(&vars->forks[num]);
	pthread_mutex_unlock(&vars->forks[(num + 1) % vars->philo_nb]);
	return (0);
}

int	philo_sleep(t_vars *vars, ssize_t num)
{
	if (vars->philo_nb == 1)
		return (0);
	lock_print(vars, num, "is sleeping");
	ft_usleep(vars->sleeping_time);
	lock_print(vars, num, "is thinking");
	return (0);
}
