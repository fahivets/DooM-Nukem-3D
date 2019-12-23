/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_clipping.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:47:16 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/14 21:29:36 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	clip_left_2_sprite(t_render *r, float *distance)
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

static void	clip_left_sprite(t_render *r, t_sdl *sdl)
{
	float distance[2];

	if (r->angle_v1 > DEG_35)
	{
		if (r->i1.y > 0 && r->i2.y > 0)
			clip_left_2_sprite(r, distance);
		else
		{
			if (r->i1.y > 0)
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
		r->la = sqrt((r->old[0].x - r->r1.x) * (r->old[0].x - r->r1.x) +
		(r->old[0].y - r->r1.y) * (r->old[0].y - r->r1.y));
		r->u0 = r->la / r->lb *
		(sdl->sprite_tex->w - 1);
	}
}

static void	clip_right_2_sprite(t_render *r, float *distance)
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

static void	clip_right_sprite(t_render *r, t_sdl *sdl)
{
	float distance[2];

	if (r->angle_v2 > DEG_35)
	{
		if (r->i1.y > 0 && r->i2.y > 0)
			clip_right_2_sprite(r, distance);
		else
		{
			if (r->i1.y > 0)
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
		r->la = sqrt((r->r2.x - r->old[1].x) * (r->r2.x - r->old[1].x) +
		(r->r2.y - r->old[1].y) * (r->r2.y - r->old[1].y));
		r->u1 = (r->lb - r->la) *
		(sdl->sprite_tex->w - 1) / r->lb;
	}
}

void		clip_sprite(t_render *r, t_sdl *sdl)
{
	r->old[0] = r->r1;
	r->old[1] = r->r2;
	r->i1 = get_intersect_coord(r->old, 1);
	r->i2 = get_intersect_coord(r->old, 2);
	r->lb = sqrt((r->r2.x - r->r1.x) * (r->r2.x - r->r1.x) +
	(r->r2.y - r->r1.y) * (r->r2.y - r->r1.y));
	clip_left_sprite(r, sdl);
	clip_right_sprite(r, sdl);
}
