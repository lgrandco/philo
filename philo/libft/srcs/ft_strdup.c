/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:50:00 by leo               #+#    #+#             */
/*   Updated: 2023/11/07 03:01:11 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	bytes;
	char	*ret;

	bytes = ft_strlen(s) + 1;
	ret = malloc(bytes);
	if (ret)
		ft_strlcpy(ret, s, bytes);
	return (ret);
}
