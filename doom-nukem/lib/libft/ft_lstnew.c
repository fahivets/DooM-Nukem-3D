/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 17:41:16 by asirenko          #+#    #+#             */
/*   Updated: 2018/10/30 18:58:36 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	void		*c;
	size_t		cz;
	t_list		*ptr;

	ptr = (t_list *)malloc(sizeof(t_list));
	if (!ptr)
		return (NULL);
	if (content == NULL)
	{
		ptr->content = NULL;
		ptr->content_size = 0;
	}
	else
	{
		c = ft_memalloc(content_size);
		cz = content_size;
		ft_memcpy(c, content, content_size);
		ptr->content = c;
		ptr->content_size = cz;
	}
	ptr->next = NULL;
	return (ptr);
}
