/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:45:36 by leo               #+#    #+#             */
/*   Updated: 2023/11/07 12:06:50 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	str_len;
	char	*ret;

	str_len = ft_strlen(s);
	if (str_len < start)
		return (ft_calloc(1, 1));
	if (str_len - start < len)
		len = str_len - start;
	ret = malloc(len + 1);
	if (ret)
		ft_strlcpy(ret, s + start, len + 1);
	return (ret);
}
