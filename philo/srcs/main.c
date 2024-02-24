/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 20:22:12 by leo               #+#    #+#             */
/*   Updated: 2024/02/24 17:04:28 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_error(char *s)
{
	fprintf(stderr, "%s", s);
	exit(EXIT_FAILURE);
}

int	all_alive(t_vars *vars)
{
	int	ret;

	pthread_mutex_lock(&vars->m_alive);
	ret = vars->alive;
	pthread_mutex_unlock(&vars->m_alive);
	return (ret);
}

int	finished_eating(t_vars *vars)
{
	int	ret;

	pthread_mutex_lock(&vars->m_count);
	ret = vars->max_meals_bool && vars->count == vars->philo_nb
		* vars->max_meals;
	pthread_mutex_unlock(&vars->m_count);
	return (ret);
}

size_t	get_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	check_deaths(t_vars *vars)
{
	size_t	i;
	size_t	ms;

	i = 0;
	ms = get_ms();
	while (i < vars->philo_nb)
	{
		if (ms - vars->last_meals[i] > vars->death_time)
		{
			printf("%ld %ld %s\n", vars->last_meals[i] + vars->death_time
				- vars->start_time, i + 1, "died");
			pthread_mutex_lock(&vars->m_alive);
			vars->alive = 0;
			pthread_mutex_unlock(&vars->m_alive);
			return (1);
		}
		i++;
	}
	return (0);
}

void	lock_print(t_vars *vars, long index, char *msg)
{
	pthread_mutex_lock(&vars->write);
	if (!all_alive(vars) || finished_eating(vars))
	{
		pthread_mutex_unlock(&vars->write);
		return ;
	}
	if (!check_deaths(vars))
		printf("%ld %ld %s\n", get_ms() - vars->start_time, index + 1, msg);
	pthread_mutex_unlock(&vars->write);
}

void	ft_usleep(size_t time)
{
	size_t	start;

	start = get_ms();
	while (get_ms() < start + time)
		usleep(500);
}

void	*funct(void *ptr)
{
	size_t	num;
	size_t	count;
	t_vars	*vars;

	vars = ptr;
	pthread_mutex_lock(&vars->incr);
	num = vars->index++;
	pthread_mutex_unlock(&vars->incr);
	count = 0;
	if (!((num + 1) % 2))
	{
		ft_usleep(2);
	}
	while (all_alive(vars) && !finished_eating(vars))
	{
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
		vars->last_meals[num] = get_ms();
		lock_print(vars, num, "is eating");
		pthread_mutex_lock(&vars->m_count);
		vars->count++;
		pthread_mutex_unlock(&vars->m_count);
		ft_usleep(vars->eating_time);
		pthread_mutex_unlock(&vars->forks[num]);
		pthread_mutex_unlock(&vars->forks[(num + 1) % vars->philo_nb]);
		lock_print(vars, num, "is sleeping");
		ft_usleep(vars->sleeping_time);
		lock_print(vars, num, "is thinking");
		if (vars->eating_time >= vars->sleeping_time && vars->philo_nb % 2)
			ft_usleep(vars->eating_time - vars->sleeping_time + 1);
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
	vars.count = 0;
	vars.start_time = get_ms();
	vars.philo_nb = ft_atoi(av[1]);
	vars.death_time = ft_atoi(av[2]);
	vars.eating_time = ft_atoi(av[3]);
	vars.sleeping_time = ft_atoi(av[4]);
	vars.max_meals_bool = (av[5] != NULL);
	if (av[5])
		vars.max_meals = ft_atoi(av[5]);
	vars.threads = malloc(sizeof(pthread_t) * vars.philo_nb);
	vars.last_meals = malloc(sizeof(*vars.last_meals) * vars.philo_nb);
	vars.forks = malloc(sizeof(pthread_mutex_t) * vars.philo_nb);
	if (!vars.threads)
		exit_error("Not enough memory\n");
	if (!vars.forks)
		exit_error("Not enough memory\n");
	i = 0;
	while (i < vars.philo_nb)
	{
		vars.last_meals[i] = get_ms();
		pthread_mutex_init(&vars.forks[i++], NULL);
	}
	i = 0;
	vars.index = 0;
	vars.alive = 1;
	vars.finished = 0;
	pthread_mutex_init(&vars.m_alive, NULL);
	pthread_mutex_init(&vars.m_count, NULL);
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
