/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:20:06 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/04 07:18:16 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	lock_print(t_vars *vars, long index, char *msg)
{
	if (!is_dead(vars, time_to_ms()))
		printf("%ld %ld %s\n", time_to_ms() - vars->start_time, index, msg);
}

int	take_forks(t_vars *vars, ssize_t num)
{
	sem_wait(vars->sem_ongoing);
	if (finished_eating(vars))
	{
		free_all(vars);
		exit(0);
	}
	sem_post(vars->sem_ongoing);
	if (vars->philo_nb == 1)
	{
		lock_print(vars, num, "has taken a fork");
		if (all_alive(vars))
			ft_usleep(vars, vars->death_time);
		return (0);
	}
	if (vars->max_meals_bool && vars->count > vars->max_meals)
	{
		free_all(vars);
		exit(0);
	}
	sem_wait(vars->sem_forks);
	lock_print(vars, num, "has taken a fork");
	sem_wait(vars->sem_forks);
	lock_print(vars, num, "has taken a fork");
	return (0);
}

int	eat(t_vars *vars, ssize_t num)
{
	if (vars->philo_nb == 1)
		return (0);
	vars->last_meals = time_to_ms();
	lock_print(vars, num, "is eating");
	vars->count++;
	ft_usleep(vars, vars->eating_time);
	sem_post(vars->sem_forks);
	sem_post(vars->sem_forks);
	return (0);
}

int	philo_sleep(t_vars *vars, ssize_t num)
{
	if (vars->philo_nb == 1)
		return (0);
	lock_print(vars, num, "is sleeping");
	ft_usleep(vars, vars->sleeping_time);
	lock_print(vars, num, "is thinking");
	return (0);
}
