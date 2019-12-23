/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 14:48:09 by asirenko          #+#    #+#             */
/*   Updated: 2018/11/03 17:38:31 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_ncount(int n)
{
	int count;
	int sign;

	sign = 1;
	count = 1;
	if (n < 0)
		sign = -1;
	while (n / (sign * 10) > 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

static	char	*ft_makestr(char *mas, int k, int sign, int n)
{
	while (k > 0)
	{
		mas[k - 1] = n % 10 + 48;
		n = n / 10;
		k--;
	}
	if (sign == -1)
		mas[k] = '-';
	return (mas);
}

char			*ft_itoa(int n)
{
	char	*mas;
	int		k;
	int		j;
	int		sign;

	sign = 1;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	k = ft_ncount(n);
	if (n < 0)
	{
		k++;
		n = n * -1;
		sign = -1;
	}
	j = k;
	mas = (char *)malloc(sizeof(char) * (k + 1));
	if (!mas)
		return (NULL);
	mas = ft_makestr(mas, k, sign, n);
	mas[j] = '\0';
	return (mas);
}
