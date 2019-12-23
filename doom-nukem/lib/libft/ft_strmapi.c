/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 21:17:55 by asirenko          #+#    #+#             */
/*   Updated: 2018/11/03 17:13:08 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*mas;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	mas = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!mas)
		return (NULL);
	while (s[i])
	{
		mas[i] = f(i, s[i]);
		i++;
	}
	mas[i] = '\0';
	return (mas);
}
