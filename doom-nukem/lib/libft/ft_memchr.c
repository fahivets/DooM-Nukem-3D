/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 16:12:54 by asirenko          #+#    #+#             */
/*   Updated: 2018/11/03 16:54:27 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	const char	*src;

	src = s;
	i = 0;
	while (i < n)
	{
		if (src[i] == (char)c)
			return ((char *)&src[i]);
		i++;
	}
	return (NULL);
}
