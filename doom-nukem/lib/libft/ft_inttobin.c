/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inttobin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 21:24:07 by asirenko          #+#    #+#             */
/*   Updated: 2018/10/31 21:24:43 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_inttobin(unsigned int nbr)
{
	if (nbr <= 1023)
	{
		if (nbr == 0)
			return (0);
		if (nbr == 1)
			return (1);
		return ((nbr % 2) + 10 * ft_inttobin(nbr / 2));
	}
	else
		return (0);
}
