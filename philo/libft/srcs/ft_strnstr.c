/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:48:23 by leo               #+#    #+#             */
/*   Updated: 2023/11/07 05:18:15 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (!*little)
		return ((void *)big);
	while (len && *big)
	{
		i = 0;
		while (i < len && little[i] && little[i] == big[i])
			i++;
		if (!little[i])
			return ((void *)big);
		big++;
		len--;
	}
	return (NULL);
}
