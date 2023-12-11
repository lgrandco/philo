/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:24:51 by legrandc          #+#    #+#             */
/*   Updated: 2023/11/07 05:37:27 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (src >= dest)
		return (ft_memcpy(dest, src, n));
	if (!n)
		return (dest);
	while (--n > 0)
		((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
	((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
	return (dest);
}
