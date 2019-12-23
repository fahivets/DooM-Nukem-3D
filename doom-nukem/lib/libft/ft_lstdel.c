/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 19:10:55 by asirenko          #+#    #+#             */
/*   Updated: 2018/11/03 18:15:59 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *ptr;

	if (!alst)
		return ;
	while (*alst)
	{
		ptr = *alst;
		del((*alst)->content, (*alst)->content_size);
		free(ptr);
		(*alst) = (*alst)->next;
	}
	free(*alst);
	*alst = NULL;
}
