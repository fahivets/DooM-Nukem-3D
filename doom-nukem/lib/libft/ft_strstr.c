/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 17:37:51 by asirenko          #+#    #+#             */
/*   Updated: 2018/10/25 22:01:55 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t		ft_stlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char				*ft_strstr(const char *haystack, const char *needle)
{
	size_t i;
	size_t j;
	size_t n;

	n = 0;
	j = 0;
	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i])
	{
		n = i;
		while (haystack[n] == needle[j] && needle[j])
		{
			n++;
			j++;
			if (j == ft_stlen(needle))
				return ((char *)&haystack[n - j]);
		}
		i++;
		j = 0;
	}
	return (0);
}
