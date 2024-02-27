/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 20:22:12 by leo               #+#    #+#             */
/*   Updated: 2024/02/27 12:03:34 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*funct(void *ptr)
{
	ssize_t	num;
	ssize_t	count;
	t_vars	*vars;

	vars = ptr;
	pthread_mutex_lock(&vars->incr);
	num = vars->index++;
	pthread_mutex_unlock(&vars->incr);
	count = 0;
	if (!((num + 1) % 2))
		ft_usleep(vars->eating_time);
	while (all_alive(vars) && !finished_eating(vars))
	{
		take_forks(vars, num);
		eat(vars, num);
		philo_sleep(vars, num);
		if (vars->eating_time >= vars->sleeping_time && vars->philo_nb % 2)
			ft_usleep(2 * vars->eating_time - vars->sleeping_time);
		count++;
	}
	return (vars);
}

int	main(int ac, char **av)
{
	t_vars	vars;
	ssize_t	i;

	if (ac < 5 || ac > 6)
		exit_error(ERR, NULL, NULL, NULL);
	init_vars(av, &vars);
	init_mut(&vars);
	i = 0;
	while (i < vars.philo_nb)
	{
		pthread_create(&vars.threads[i], NULL, funct, &vars);
		i++;
	}
	i = 0;
	while (i < vars.philo_nb)
	{
		pthread_join(vars.threads[i], NULL);
		i++;
	}
	free_all(&vars);
}
