/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:54:42 by asirenko          #+#    #+#             */
/*   Updated: 2018/10/26 17:11:17 by asirenko         ###   ########.fr       */
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

char				*ft_strnstr(const char *s1, const char *s2, size_t ln)
{
	size_t i;
	size_t j;
	size_t n;

	n = 0;
	j = 0;
	i = 0;
	if (s2[0] == '\0')
		return ((char *)s1);
	while (s1[i] && i < ln)
	{
		n = i;
		while (s1[n] == s2[j] && s2[j])
		{
			n++;
			j++;
			if (j == ft_stlen(s2) && n <= ln)
				return ((char *)&s1[n - j]);
		}
		i++;
		j = 0;
	}
	return (0);
}
