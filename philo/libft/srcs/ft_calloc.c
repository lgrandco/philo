/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:49:25 by leo               #+#    #+#             */
/*   Updated: 2023/11/06 16:52:08 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	int		i;
	size_t	memory;
	void	*ret;

	i = 0;
	memory = nmemb * size;
	if (size && nmemb != memory / size)
		return (NULL);
	ret = malloc(memory);
	if (ret)
		ft_bzero(ret, memory);
	return (ret);
}
