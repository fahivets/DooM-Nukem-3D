/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 17:06:10 by asirenko          #+#    #+#             */
/*   Updated: 2019/09/18 18:41:14 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_xy			get_intersect_coord(t_xy *v, int side)
{
	t_xy	tmp;
	float	x3;
	float	x4;

	x3 = NEARX;
	x4 = FARX;
	if (side == 2)
	{
		x3 *= -1;
		x4 *= -1;
	}
	tmp.x = VCP(VCP(v[0].x, v[0].y, v[1].x, v[1].y), v[0].x - v[1].x,
	VCP(x3, NEARY, x4, FARY), x3 - x4) /
	VCP(v[0].x - v[1].x, v[0].y - v[1].y, x3 - x4, NEARY - FARY);
	tmp.y = VCP(VCP(v[0].x, v[0].y, v[1].x, v[1].y), v[0].y - v[1].y,
	VCP(x3, NEARY, x4, FARY), NEARY - FARY) /
	VCP(v[0].x - v[1].x, v[0].y - v[1].y, x3 - x4, NEARY - FARY);
	return (tmp);
}

static float	area(t_xy v1, t_xy v2, t_xy v3)
{
	return (v2.x - v1.x) * (v3.y - v1.y) - (v2.y - v1.y) * (v3.x - v1.x);
}

static int		intersect_1(float a, float b, float c, float d)
{
	float tmp;

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

int				intersection(t_xy *v, int side)
{
	if (side == 2)
	{
		v[2].x *= -1;
		v[3].x *= -1;
	}
	return (
		intersect_1(v[0].x, v[1].x, v[2].x, v[3].x) &&
		intersect_1(v[0].y, v[1].y, v[2].y, v[3].y) &&
		area(v[0], v[1], v[2]) * area(v[0], v[1], v[3]) <= 0 &&
		area(v[2], v[3], v[0]) * area(v[2], v[3], v[1]) <= 0);
}

int				check_wall_intersect_with_view_lines(t_render *render)
{
	t_xy	v[4];

	v[0] = render->r1;
	v[1] = render->r2;
	v[2].x = NEARX;
	v[2].y = NEARY;
	v[3].x = FARX * 1e8;
	v[3].y = FARY * 1e8;
	if (intersection(v, 1) | intersection(v, 2))
		return (1);
	return (0);
}
