/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 20:32:30 by asirenko          #+#    #+#             */
/*   Updated: 2018/11/03 17:44:29 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*ptr;
	t_list	*result;

	if (!lst)
		return (NULL);
	ptr = (t_list *)malloc(sizeof(t_list));
	if (!ptr)
		return (NULL);
	result = NULL;
	if (lst)
	{
		ptr = (*f)(lst);
		result = ptr;
		while (lst->next != NULL)
		{
			ptr->next = (*f)(lst->next);
			ptr = ptr->next;
			lst = lst->next;
		}
		ptr->next = NULL;
	}
	return (result);
}
