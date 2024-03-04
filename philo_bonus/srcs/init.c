/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 08:16:55 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/04 06:47:40 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_sem(t_vars *vars)
{
	sem_unlink(FORKS_FILE);
	sem_unlink(FINISHED_FILE);
	vars->sem_ongoing = sem_open(FINISHED_FILE, O_CREAT, O_RDWR, 1);
	vars->sem_forks = sem_open(FORKS_FILE, O_CREAT, O_RDWR, vars->philo_nb);
	vars->start_time = time_to_ms();
}

void	init_vars(char **av, t_vars *vars)
{
	vars->max_meals = 1;
	vars->philo_nb = ft_atoi(av[1]);
	vars->death_time = ft_atoi(av[2]);
	vars->eating_time = ft_atoi(av[3]);
	vars->sleeping_time = ft_atoi(av[4]);
	vars->max_meals_bool = (av[5] != NULL);
	if (vars->max_meals_bool)
		vars->max_meals = ft_atoi(av[5]);
	if (vars->philo_nb < 1 || vars->death_time < 1 || vars->eating_time < 1
		|| vars->sleeping_time < 1 || vars->max_meals < 1)
		exit_error("Incorrect argument\n" ERR, (void *[]){0, 0, 0});
	vars->index = 0;
	vars->alive = 1;
	vars->count = 0;
	vars->pids = malloc(sizeof(*vars->pids) * vars->philo_nb);
	if (!vars->pids)
		exit_error("Malloc error\n", (void *[]){0, 0, 0});
}
