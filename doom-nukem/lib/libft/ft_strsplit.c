/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooliinyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 21:22:56 by ooliinyk          #+#    #+#             */
/*   Updated: 2018/11/03 21:23:01 by ooliinyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_word(char const *s, char c, int a)
{
	int		i;
	char	*str;

	if (!s || !c)
		return (NULL);
	i = a;
	while (s[i] != c && s[i])
		i++;
	i -= a;
	if (!(str = (char*)malloc(sizeof(char) * i + 1)))
		return (NULL);
	i = 0;
	while (s[a] != c && s[a])
		str[i++] = s[a++];
	str[i] = '\0';
	return (str);
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	char	**str;

	if (!s || !c)
		return (NULL);
	i = 0;
	j = 0;
	if (!(str = (char**)malloc(sizeof(char*) * (ft_wrdcnt(s, c) + 1))))
		return (NULL);
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		if (s[i] != c && s[i])
			str[j] = ft_word(s, c, i);
		j++;
		while (s[i] != c && s[i])
			i++;
		while (s[i] == c && s[i])
			i++;
	}
	str[j] = 0;
	return (str);
}
