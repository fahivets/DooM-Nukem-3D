/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 17:29:00 by asirenko          #+#    #+#             */
/*   Updated: 2018/10/27 21:31:18 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_stlen(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t			ft_strlcat(char *restrict dst, const char *restrict src,
		size_t dstsize)
{
	size_t i;
	size_t j;
	size_t k;

	i = 0;
	k = dstsize;
	while (dst[i] != '\0' && i < k)
		i++;
	j = i;
	while (src[i - j] != '\0' && j + 1 < k)
	{
		dst[i] = src[i - j];
		i++;
		k--;
	}
	if (i < dstsize)
		dst[i] = '\0';
	return (ft_stlen((char *)src) + j);
}
