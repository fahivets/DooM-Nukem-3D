/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 17:03:24 by asirenko          #+#    #+#             */
/*   Updated: 2019/07/11 17:22:05 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_startskip(char const *s)
{
	int i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	return (i);
}

static	int	ft_endskip(char const *s)
{
	int k;

	k = ft_strlen(s);
	while (s[k - 1] == ' ' || s[k - 1] == '\n' || s[k - 1] == '\t')
		k--;
	return (k);
}

char		*ft_strtrim(char const *s)
{
	int		i;
	int		len;
	char	*m;
	int		k;

	if (!s)
		return (NULL);
	len = 0;
	i = ft_startskip(s);
	if (s[i] == '\0')
	{
		m = (char *)malloc(sizeof(char));
		if (!m)
			return (NULL);
		m[0] = '\0';
		return (m);
	}
	k = ft_endskip(s);
	m = (char *)malloc(sizeof(char) * (k - i + 1));
	if (!m)
		return (NULL);
	while (i < k)
		m[len++] = s[i++];
	m[len] = '\0';
	return (m);
}
