/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 20:22:12 by leo               #+#    #+#             */
/*   Updated: 2024/02/28 06:09:10 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*funct(void *ptr)
{
	ssize_t	num;
	t_vars	*vars;

	vars = ptr;
	pthread_mutex_lock(&vars->incr);
	num = vars->index++;
	pthread_mutex_unlock(&vars->incr);
	if (!((num + 1) % 2))
		ft_usleep(vars, vars->eating_time);
	while (all_alive(vars) && !finished_eating(vars))
	{
		take_forks(vars, num);
		printf("z\n");
		eat(vars, num);
		philo_sleep(vars, num);
		lock_print(vars, num, "is thinking");
		if (vars->eating_time >= vars->sleeping_time && vars->philo_nb % 2)
			ft_usleep(vars, 2 * vars->eating_time - vars->sleeping_time);
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
	init_mut(&vars);
	check_deaths(&vars);
	i = 0;
	while (i < vars.philo_nb)
	{
		pthread_create(&vars.threads[i], NULL, funct, &vars);
		i++;
	}
	clear_threads(&vars);
	free_all(&vars);
}
