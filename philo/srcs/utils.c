/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:47:27 by legrandc          #+#    #+#             */
/*   Updated: 2024/02/28 06:07:04 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

ssize_t	time_to_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(t_vars *vars, ssize_t time)
{
	ssize_t	start;

	start = time_to_ms();
	while (time_to_ms() < start + time)
	{
		usleep(500);
		if (!all_alive(vars) || finished_eating(vars))
			return ;
	}
	(void)vars;
}

void	exit_error(char *s, void **t)
{
	fprintf(stderr, "%s", s);
	free(t[0]);
	free(t[1]);
	free(t[2]);
	exit(EXIT_FAILURE);
}

int	alloc_and_cpy(void **dest, t_vars *vars, ssize_t n)
{
	ssize_t				i;
	unsigned char		*p;
	const unsigned char	*p2;
	int					e;

	*dest = malloc(n);
	if (!(*dest))
		return (-1);
	p2 = (void *)vars->last_meals;
	p = *dest;
	i = 0;
	pthread_mutex_lock(&vars->m_meal);
	while (i < n)
	{
		e = p2[i];
		p[i] = p2[i];
		i++;
	}
	pthread_mutex_unlock(&vars->m_meal);
	return (0);
}

void	free_all(t_vars *vars)
{
	free(vars->threads);
	free(vars->last_meals);
	free(vars->forks);
}
