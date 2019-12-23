/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkinzers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 20:36:32 by kkinzers          #+#    #+#             */
/*   Updated: 2019/09/04 20:36:34 by kkinzers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

double	area1(t_ed *e, double x3, double y3)
{
	return (e->in.x2 - e->in.x1) * (y3 - e->in.y1) - (e->in.y2 - e->in.y1) *
	(x3 - e->in.x1);
}

double	area2(t_ed *e, double x3, double y3)
{
	return (e->in.x4 - e->in.x3) * (y3 - e->in.y3) - (e->in.y4 - e->in.y3) *
	(x3 - e->in.x3);
}

int		intersect_1(double a, double b, double c, double d)
{
	double	tmp;

	if (a > b)
	{
		tmp = a;
		a = b;
		b = tmp;
	}
	if (c > d)
	{
		tmp = c;
		c = d;
		d = tmp;
	}
	if (MAX(a, c) <= MIN(b, d))
		return (1);
	return (0);
}

int		intersection(t_ed *e)
{
	return (intersect_1(e->in.x1, e->in.x2, e->in.x3, e->in.x4) &&
		intersect_1(e->in.y1, e->in.y2, e->in.y3, e->in.y4) &&
		area1(e, e->in.x3, e->in.y3) * area1(e, e->in.x4, e->in.y4) <= 0 &&
		area2(e, e->in.x1, e->in.y1) * area2(e, e->in.x2, e->in.y2) <= 0);
}
