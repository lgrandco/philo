/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:07:40 by leo               #+#    #+#             */
/*   Updated: 2023/11/07 03:33:23 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*ret;

	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	if (!s1[i])
		return (ft_strdup(""));
	start = i;
	while (s1[i])
		i++;
	i--;
	while (s1[i] && ft_strchr(set, s1[i]))
		i--;
	end = i + 1;
	ret = malloc(end - start + 1);
	if (ret)
		ft_strlcpy(ret, s1 + start, end - start + 1);
	return (ret);
}
