/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 23:19:32 by asirenko          #+#    #+#             */
/*   Updated: 2018/11/03 16:49:39 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*k;
	size_t			i;

	k = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		k[i] = c;
		i++;
	}
	b = k;
	return (b);
}
