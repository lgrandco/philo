/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 00:38:51 by legrandc          #+#    #+#             */
/*   Updated: 2024/02/28 00:53:57 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clear_threads(t_vars *vars)
{
	ssize_t	i;

	i = 0;
	while (i < vars->philo_nb)
	{
		pthread_join(vars->threads[i], NULL);
		i++;
	}
}
