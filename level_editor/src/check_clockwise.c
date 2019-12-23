/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_clockwise.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkinzers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 00:40:43 by kkinzers          #+#    #+#             */
/*   Updated: 2019/10/16 00:40:44 by kkinzers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void			sort_dots(t_ed *e)
{
	int			all_dots[e->number + 1];
	int			c;
	int			i;

	i = -1;
	c = 0;
	while (c < e->number + 1)
	{
		i = -1;
		while (++i < DOTS_H * DOTS_W)
			if (e->d[i].num_in_sect == c)
			{
				all_dots[c] = i;
				c++;
			}
	}
	i = 0;
	while (++i < e->number + 1)
		e->d[all_dots[i]].num_in_sect = e->number + 1 - i;
}

int				check_clock(t_ed *e, double *x, double *y)
{
	int			wall;
	long double	sum;

	wall = 0;
	sum = 0;
	while (wall <= e->number - 1)
	{
		sum += x[wall] * y[wall + 1] - x[wall + 1] * y[wall];
		wall++;
	}
	if (wall == e->number)
	{
		sum += x[wall] * y[0] - x[0] * y[wall];
	}
	if (sum < 0)
		return (0);
	else
		return (1);
}

void			clockwise(t_ed *e)
{
	int			i;
	double		x[e->number];
	double		y[e->number];
	int			l_number;

	i = -1;
	l_number = 0;
	while (++i < DOTS_H * DOTS_W)
	{
		if (e->d[i].num_in_sect == l_number)
		{
			x[l_number] = e->d[i].x;
			y[l_number] = e->d[i].y;
			i = -1;
			l_number++;
		}
	}
	if (!check_clock(e, x, y))
		sort_dots(e);
}
