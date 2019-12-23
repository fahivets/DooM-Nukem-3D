/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 19:01:08 by asirenko          #+#    #+#             */
/*   Updated: 2018/11/03 18:16:52 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	t_list *ptr;

	if (!alst)
		return ;
	ptr = *alst;
	if (alst)
	{
		del(ptr->content, ptr->content_size);
		free(*alst);
		*alst = NULL;
	}
}
