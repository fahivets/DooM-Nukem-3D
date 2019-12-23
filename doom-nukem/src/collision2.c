/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 13:55:48 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/15 14:30:45 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

bool			lci(float x, float y, double r, t_wall w)
{
	float dx;
	float dy;
	float a;
	float b;
	float c;

	w.v1.x -= x;
	w.v1.y -= y;
	w.v2.x -= x;
	w.v2.y -= y;
	dx = w.v2.x - w.v1.x;
	dy = w.v2.y - w.v1.y;
	a = dx * dx + dy * dy;
	b = 2 * (w.v1.x * dx + w.v1.y * dy);
	c = w.v1.x * w.v1.x + w.v1.y * w.v1.y - r * r;
	if (-b < 0)
		return (c < 0);
	if (-b < (2 * a))
		return ((4 * a * c - b * b) < 0);
	return (a + b + c < 0);
}

static float	dot_prod(float x1, float x2, float y1, float y2)
{
	return (x1 * x2 + y1 * y2);
}

void			get_desired_motion(float *dx, float *dy, t_wall w)
{
	t_xy line;
	t_xy normal;
	t_xy um;
	t_xy dm;

	line.x = w.v2.x - w.v1.x;
	line.y = w.v2.y - w.v1.y;
	normal.x = -line.y / sqrt(line.x * line.x + line.y * line.y);
	normal.y = line.x / sqrt(line.x * line.x + line.y * line.y);
	um.x = normal.x * dot_prod(*dx, normal.x, *dy, normal.y);
	um.y = normal.y * dot_prod(*dx, normal.x, *dy, normal.y);
	dm.x = *dx - um.x;
	dm.y = *dy - um.y;
	*dx = dm.x;
	*dy = dm.y;
}
