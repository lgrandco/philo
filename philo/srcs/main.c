/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 20:22:12 by leo               #+#    #+#             */
/*   Updated: 2023/12/10 21:09:43 by leo              ###   ########.fr       */
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
	size_t			num;
	pthread_mutex_t	lock;
	size_t			count;
	t_vars			*vars;
	size_t			last_meal;

	vars = ptr;
	last_meal = vars->start_time;
	pthread_mutex_init(&lock, NULL);
	num = vars->index++;
	count = 0;
	while (!vars->max_meals_bool || count < vars->max_meals)
	{
		if (get_ms() - last_meal >= vars->death_time)
		{
			printf("%ld rip\n", num);
			exit(1);
		}
		if (!vars->forks[num] && !vars->forks[(num + 1) % vars->philo_nb])
		{
			pthread_mutex_lock(&lock);
			vars->forks[num] = 1;
			vars->forks[(num + 1) % vars->philo_nb] = 1;
			pthread_mutex_unlock(&lock);
			printf("%ld fork\n", num);
			printf("%ld fork\n", num);
			last_meal = get_ms();
			printf("%ld eat\n", num);
			usleep(vars->eating_time * 1000);
			printf("%ld sleep\n", num);
			pthread_mutex_lock(&lock);
			vars->forks[num] = 0;
			vars->forks[(num + 1) % vars->philo_nb] = 0;
			pthread_mutex_unlock(&lock);
			usleep(vars->sleeping_time * 1000);
			printf("%ld thinking\n", num);
			count++;
		}
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
	if (!vars.threads)
		exit_error("Not enough memory\n");
	vars.forks = malloc(sizeof(int) * vars.philo_nb);
	if (!vars.forks)
		exit_error("Not enough memory\n");
	memset(vars.forks, 0, vars.philo_nb * sizeof(int));
	i = 0;
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
	// sleep(1);
}
