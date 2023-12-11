/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 23:03:25 by leo               #+#    #+#             */
/*   Updated: 2023/11/26 16:13:00 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content, int n)
{
	t_list	*ret;

	ret = malloc(sizeof(*ret));
	if (!ret)
		return (NULL);
	ret->n = n;
	ret->content = content;
	ret->next = NULL;
	return (ret);
}
