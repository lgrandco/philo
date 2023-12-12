/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 20:22:12 by leo               #+#    #+#             */
/*   Updated: 2023/12/12 09:42:33 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_error(char *s)
{
	fprintf(stderr, "%s", s);
	exit(EXIT_FAILURE);
}

size_t	get_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	*funct(void *ptr)
{
	size_t	num;
	size_t	count;
	t_vars	*vars;
	size_t	last_meal;

	vars = ptr;
	last_meal = vars->start_time;
	num = vars->index++;
	count = 0;
	while (!vars->max_meals_bool || count < vars->max_meals)
	{
		pthread_mutex_lock(&vars->forks[num]);
		pthread_mutex_lock(&vars->forks[(num + 1) % vars->philo_nb]);
		if (get_ms() - last_meal >= vars->death_time)
		{
			printf("%ld %ld %ld rip\n", last_meal + vars->death_time
				- vars->start_time, num, get_ms() - last_meal);
			exit(1);
		}
		printf("%ld %ld fork\n", get_ms() - vars->start_time, num);
		printf("%ld %ld fork\n", get_ms() - vars->start_time, num);
		last_meal = get_ms();
		printf("%ld %ld eat\n", get_ms() - vars->start_time, num);
		usleep(vars->eating_time * 1000);
		pthread_mutex_unlock(&vars->forks[num]);
		pthread_mutex_unlock(&vars->forks[(num + 1) % vars->philo_nb]);
		printf("%ld %ld sleep\n", get_ms() - vars->start_time, num);
		usleep(vars->sleeping_time * 1000);
		printf("%ld %ld thinking\n", get_ms() - vars->start_time, num);
		count++;
	}
	return (vars);
}

int	main(int ac, char **av)
{
	int		n;
	int		n2;
	t_vars	vars;
	size_t	i;

	n = 0;
	n2 = 0;
	if (ac < 5 || ac > 6)
		exit_error(ERR);
	vars.start_time = get_ms();
	vars.philo_nb = ft_atoi(av[1]);
	vars.death_time = ft_atoi(av[2]);
	vars.eating_time = ft_atoi(av[3]);
	vars.sleeping_time = ft_atoi(av[4]);
	vars.max_meals_bool = (av[5] != NULL);
	if (av[5])
		vars.max_meals = ft_atoi(av[5]);
	vars.threads = malloc(sizeof(pthread_t) * vars.philo_nb);
	vars.forks = malloc(sizeof(pthread_mutex_t) * vars.philo_nb);
	if (!vars.threads)
		exit_error("Not enough memory\n");
	if (!vars.forks)
		exit_error("Not enough memory\n");
	i = 0;
	while (i < vars.philo_nb)
		pthread_mutex_init(&vars.forks[i++], NULL);
	i = 0;
	vars.index = 0;
	while (i < vars.philo_nb)
	{
		pthread_create(&vars.threads[i++], NULL, funct, &vars);
	}
	i = 0;
	while (i < vars.philo_nb)
	{
		pthread_join(vars.threads[i++], NULL);
	}
}
