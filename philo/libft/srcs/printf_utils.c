/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:38:33 by leo               #+#    #+#             */
/*   Updated: 2023/11/19 04:34:51 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init(t_struct *vars)
{
	vars->dash = 0;
	vars->zero = 0;
	vars->hash = 0;
	vars->space = 0;
	vars->plus = 0;
	vars->star = 0;
	vars->dot = 0;
	vars->precision = 0;
	vars->percent = 0;
	vars->is_pos = 0;
	vars->is_nul = 0;
	vars->is_neg = 0;
	vars->width = 0;
	vars->hex_low = 0;
	vars->hex_up = 0;
	vars->is_str = 0;
	vars->string = NULL;
}

void	setflag(char c, t_struct *vars)
{
	if (c == '-')
		vars->dash = 1;
	else if (c == '0')
		vars->zero = 1;
	else if (c == ' ')
		vars->space = 1;
	else if (c == '+')
		vars->plus = 1;
	else if (c == '.')
		vars->dot = 1;
	else if (c == '#')
		vars->hash = 1;
}
