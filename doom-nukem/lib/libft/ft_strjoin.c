/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 20:38:08 by asirenko          #+#    #+#             */
/*   Updated: 2018/11/03 17:25:51 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*mas;
	int		i;
	int		j;
	size_t	size;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	size = ft_strlen(s1) + ft_strlen(s2);
	mas = (char *)malloc(sizeof(char) * (size + 1));
	if (!mas)
		return (NULL);
	while (s1[j])
	{
		mas[j] = s1[j];
		j++;
	}
	while (s2[i])
		mas[j++] = s2[i++];
	mas[j] = '\0';
	return (mas);
}
