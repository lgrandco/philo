/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:47:29 by leo               #+#    #+#             */
/*   Updated: 2023/12/10 05:44:57 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *nptr)
{
	int	ret;
	int	sign;

	ret = 0;
	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (ft_isdigit(*nptr))
	{
		ret = ret * 10 + *nptr - '0';
		nptr++;
	}
	return (ret * sign);
}
