/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slope_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 21:01:01 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/16 14:49:37 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

float			distance_between_point_and_line(float x, float y, t_wall wall)
{
	float distance;

	distance = fabs((wall.v2.y - wall.v1.y) * x - (wall.v2.x - wall.v1.x) *
	y + wall.v2.x * wall.v1.y - wall.v2.y * wall.v1.x) /
	sqrt((wall.v2.y - wall.v1.y) * (wall.v2.y - wall.v1.y) +
	(wall.v2.x - wall.v1.x) * (wall.v2.x - wall.v1.x));
	return (distance);
}

float			calc_slope_h_sprite(t_sector s, t_sprite sprite)
{
	float distance1;
	float distance2;
	float px;
	float py;
	float slope_h;

	px = sprite.position.x;
	py = sprite.position.y;
	distance1 = distance_between_point_and_line(px, py, s.lwall);
	distance2 = distance_between_point_and_line(px, py, s.hwall);
	slope_h = s.floor_slope * (distance1 / (distance1 + distance2));
	return (slope_h);
}

float			calc_slope_h(t_sector s, t_data *d)
{
	float distance1;
	float distance2;
	float px;
	float py;
	float slope_h;

	px = d->player.position.x;
	py = d->player.position.y;
	distance1 = distance_between_point_and_line(px, py, s.lwall);
	distance2 = distance_between_point_and_line(px, py, s.hwall);
	slope_h = s.floor_slope * (distance1 / (distance1 + distance2));
	return (slope_h);
}

void			slope_move(t_data *d)
{
	if (d->sectors[d->player.current_sector].slope)
	{
		d->player.position.z = d->sectors[d->player.current_sector].floor +
		d->player.height +
		calc_slope_h(d->sectors[d->player.current_sector], d);
	}
}
