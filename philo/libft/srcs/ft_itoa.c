/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:24:17 by leo               #+#    #+#             */
/*   Updated: 2023/11/07 04:32:14 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	long int	nb;
	size_t		len;
	char		*ret;

	nb = n;
	len = n == 0;
	if (nb < 0 && ++len)
		nb = -nb;
	while (n && ++len)
		n /= 10;
	ret = ft_calloc(len + 1, 1);
	if (!ret)
		return (NULL);
	*ret = '-';
	if (!nb)
		*ret = '0';
	while (nb)
	{
		ret[--len] = nb % 10 + '0';
		nb /= 10;
	}
	return (ret);
}
