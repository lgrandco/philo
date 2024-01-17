/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cqin <cqin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 20:22:12 by leo               #+#    #+#             */
/*   Updated: 2024/01/17 19:43:13 by cqin             ###   ########.fr       */
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

size_t	get_current_time(void)
{
	struct timeval	time;

	return (time.tv_sec * 1000000 + time.tv_usec);
}

void	lock_print(t_vars *vars, int time, int index, char *msg)
{
	pthread_mutex_lock(&vars->write);
	if (vars->dead == 0)
	{
		printf("%d %d %s\n", time, index + 1, msg);
	}
	pthread_mutex_unlock(&vars->write);
}

void	ft_usleep(size_t time)
{
	size_t	start;

	start = get_current_time();
	while (get_current_time() < start + time)
		usleep(500);
}

void	*funct(void *ptr)
{
	size_t	num;
	size_t	count;
	t_vars	*vars;
	size_t	last_meal;

	vars = ptr;
	last_meal = vars->start_time;
	pthread_mutex_lock(&vars->incr);
	num = vars->index++;
	pthread_mutex_unlock(&vars->incr);
	count = 0;
	if (!((num + 1) % 2))
	{
		// ft_usleep(500);
	}
	while (!vars->max_meals_bool || count < vars->max_meals)
	{
		if ((num + 1) % 2 == 0)
		{
			pthread_mutex_lock(&vars->forks[(num + 1) % vars->philo_nb]);
			lock_print(vars, get_ms() - vars->start_time, num, "fork r");
			pthread_mutex_lock(&vars->forks[num]);
			usleep(1000);
			lock_print(vars, get_ms() - vars->start_time, num, "fork l");
		}
		else
		{
			pthread_mutex_lock(&vars->forks[num]);
			lock_print(vars, get_ms() - vars->start_time, num, "fork l");
			usleep(1000);
			pthread_mutex_lock(&vars->forks[(num + 1) % vars->philo_nb]);
			lock_print(vars, get_ms() - vars->start_time, num, "fork r");
		}
		if (get_ms() - last_meal >= vars->death_time)
		{
			pthread_mutex_lock(&vars->write);
			if (vars->dead == 0)
				printf("%ld %ld %s\n %ld\n", last_meal + vars->death_time
					- vars->start_time, num + 1, "died", get_ms() - last_meal
					- vars->death_time);
			vars->dead = 1;
			pthread_mutex_unlock(&vars->write);
			exit(1);
			return (NULL);
		}
		last_meal = get_ms();
		lock_print(vars, get_ms() - vars->start_time, num, "eat");
		usleep(vars->eating_time * 1000);
		if ((num + 1) % 2 == 0)
		{
			printf("fwf unlocked %ld right\n", num + 1);
			pthread_mutex_unlock(&vars->forks[(num + 1) % vars->philo_nb]);
			printf("fwf unlocked %ld left\n", num + 1);
			pthread_mutex_unlock(&vars->forks[num]);
		}
		else
		{
			printf("fwf unlocked %ld left\n", num + 1);
			pthread_mutex_unlock(&vars->forks[num]);
			printf("fwf unlocked %ld right\n", num + 1);
			pthread_mutex_unlock(&vars->forks[(num + 1) % vars->philo_nb]);
		}
		lock_print(vars, get_ms() - vars->start_time, num, "sleep");
		usleep(vars->sleeping_time * 1000);
		lock_print(vars, get_ms() - vars->start_time, num, "is thinking");
		// usleep(1000);
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
	vars.dead = 0;
	pthread_mutex_init(&vars.write, NULL);
	pthread_mutex_init(&vars.dead_lock, NULL);
	pthread_mutex_init(&vars.incr, NULL);
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
