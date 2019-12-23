/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 20:47:26 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/15 13:52:03 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	clip_left_2(t_render *r, float *distance)
{
	distance[0] = sqrt((r->r1.x - r->i1.x) * (r->r1.x - r->i1.x) +
	(r->r1.y - r->i1.y) * (r->r1.y - r->i1.y));
	distance[1] = sqrt((r->r1.x - r->i2.x) * (r->r1.x - r->i2.x) +
	(r->r1.y - r->i2.y) * (r->r1.y - r->i2.y));
	if (distance[0] < distance[1])
	{
		r->r1.x = r->i1.x;
		r->r1.y = r->i1.y;
	}
	else
	{
		r->r1.x = r->i2.x;
		r->r1.y = r->i2.y;
	}
}

static void	clip_left(t_render *r, t_sector s, t_sdl *sdl)
{
	float distance[2];

	if (r->angle_v1 > DEG_35)
	{
		if (r->i1.y > 0 && r->i2.y > 0)
			clip_left_2(r, distance);
		else
		{
			if (r->i1.y > 0)
				r->r1 = r->i1;
			else
				r->r1 = r->i2;
		}
		r->la = sqrt((r->old[0].x - r->r1.x) * (r->old[0].x - r->r1.x) +
		(r->old[0].y - r->r1.y) * (r->old[0].y - r->r1.y));
		r->u0 = r->la / r->lb * (sdl->wall_texture->w - 1);
		r->u0_bot = r->la / r->lb * (sdl->bot_wall_texture->w - 1);
		r->u0_top = r->la / r->lb * (sdl->top_wall_texture->w - 1);
	}
	clip_left_slope(r, s);
}

static void	clip_right_2(t_render *r, float *distance)
{
	distance[0] = sqrt((r->r2.x - r->i1.x) * (r->r2.x - r->i1.x) +
	(r->r2.y - r->i1.y) * (r->r2.y - r->i1.y));
	distance[1] = sqrt((r->r2.x - r->i2.x) * (r->r2.x - r->i2.x) +
	(r->r2.y - r->i2.y) * (r->r2.y - r->i2.y));
	if (distance[0] < distance[1])
	{
		r->r2.x = r->i1.x;
		r->r2.y = r->i1.y;
	}
	else
	{
		r->r2.x = r->i2.x;
		r->r2.y = r->i2.y;
	}
}

static void	clip_right(t_render *r, t_sector s, t_sdl *sdl)
{
	float distance[2];

	if (r->angle_v2 > DEG_35)
	{
		if (r->i1.y > 0 && r->i2.y > 0)
			clip_right_2(r, distance);
		else
		{
			if (r->i1.y > 0)
				r->r2 = r->i1;
			else
				r->r2 = r->i2;
		}
		r->la = sqrt((r->r2.x - r->old[1].x) * (r->r2.x - r->old[1].x) +
		(r->r2.y - r->old[1].y) * (r->r2.y - r->old[1].y));
		r->u1 = (r->lb - r->la) * (sdl->wall_texture->w - 1) / r->lb;
		r->u1_bot = (r->lb - r->la) * (sdl->bot_wall_texture->w - 1) / r->lb;
		r->u1_top = (r->lb - r->la) * (sdl->top_wall_texture->w - 1) / r->lb;
	}
	clip_right_slope(r, s);
}

void		clip_wall(t_render *r, t_sector s, t_sdl *sdl)
{
	r->old[0] = r->r1;
	r->old[1] = r->r2;
	r->i1 = get_intersect_coord(r->old, 1);
	r->i2 = get_intersect_coord(r->old, 2);
	r->lb = sqrt((r->r2.x - r->r1.x) * (r->r2.x - r->r1.x) +
	(r->r2.y - r->r1.y) * (r->r2.y - r->r1.y));
	clip_left(r, s, sdl);
	clip_right(r, s, sdl);
}
