/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:47:27 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/04 06:45:54 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	while (time_to_ms() < start + time && !is_dead(vars, time_to_ms()))
		usleep(500);
}

void	exit_error(char *s, void **t)
{
	printf("%s", s);
	free(t[0]);
	free(t[1]);
	free(t[2]);
	exit(EXIT_FAILURE);
}

void	*alloc_and_cpy(const void *src, ssize_t n)
{
	ssize_t				i;
	unsigned char		*p;
	const unsigned char	*p2;
	void				*dest;

	dest = malloc(n);
	if (!dest)
		return (NULL);
	p2 = src;
	p = dest;
	i = 0;
	while (i < n)
	{
		p[i] = p2[i];
		i++;
	}
	return (dest);
}

void	free_all(t_vars *vars)
{
	free(vars->pids);
	sem_close(vars->sem_forks);
	sem_close(vars->sem_ongoing);
}
