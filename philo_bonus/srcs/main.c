/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 20:22:12 by leo               #+#    #+#             */
/*   Updated: 2024/03/04 01:16:51 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*funct(void *ptr, int num)
{
	t_vars	*vars;

	vars = ptr;
	vars->philo_index = num + 1;
	vars->last_meals = time_to_ms();
	if (!(vars->philo_index % 2))
		ft_usleep(vars, vars->eating_time);
	while (1)
	{
		take_forks(vars, vars->philo_index);
		eat(vars, vars->philo_index);
		philo_sleep(vars, vars->philo_index);
		if (vars->eating_time >= vars->sleeping_time && vars->philo_nb % 2)
			ft_usleep(vars, 2 * vars->eating_time - vars->sleeping_time);
		else
			ft_usleep(vars, vars->eating_time - vars->sleeping_time);
	}
	return (vars);
}

int	main(int ac, char **av)
{
	t_vars	vars;
	ssize_t	i;

	if (ac < 5 || ac > 6)
		exit_error(ERR, (void *[]){0, 0, 0});
	init_vars(av, &vars);
	init_sem(&vars);
	i = 0;
	while (i < vars.philo_nb)
	{
		vars.pids[i] = fork();
		if (vars.pids[i] == -1)
			exit_error("Fork error\n", (void *[]){vars.pids, 0, 0});
		else if (vars.pids[i] == 0)
			funct(&vars, i);
		i++;
	}
	wait(NULL);
	i = 0;
	while (i < vars.philo_nb)
		kill(vars.pids[i++], SIGKILL);
	free_all(&vars);
}
