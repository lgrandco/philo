/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:45:10 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/04 07:18:33 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	finished_eating(t_vars *vars)
{
	if (vars->max_meals_bool && vars->count >= vars->max_meals)
		return (1);
	return (0);
}

int	is_dead(t_vars *vars, ssize_t ms)
{
	sem_wait(vars->sem_ongoing);
	if (ms - vars->last_meals > vars->death_time)
	{
		printf("%ld %ld %s\n", time_to_ms() - vars->start_time,
			vars->philo_index, "died");
		free_all(vars);
		exit(0);
	}
	sem_post(vars->sem_ongoing);
	return (0);
}

int	all_alive(t_vars *vars)
{
	int	ret;

	ret = vars->alive;
	return (ret);
}
