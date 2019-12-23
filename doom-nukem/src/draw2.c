/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 17:40:32 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/16 21:35:44 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		calculate_repeat(t_render *r, float *repeat)
{
	float wall_len;

	wall_len = sqrt((r->t2.x - r->t1.x) * (r->t2.x - r->t1.x) +
	(r->t2.y - r->t1.y) * (r->t2.y - r->t1.y));
	repeat[0] = wall_len * 50 / r->sdl->wall_texture->w;
	if (r->s.doors[r->ii])
		repeat[0] = 1;
	repeat[2] = wall_len * 50 / r->sdl->bot_wall_texture->w;
	repeat[1] = wall_len * 50 / r->sdl->top_wall_texture->w;
}

void		calculate_texture_x(t_render *r, float *repeat)
{
	r->txtx = (r->u0 * repeat[0] * ((r->s3.x - r->x) * r->r2.y) + r->u1 * repeat
	[0] * ((r->x - r->s1.x) * r->r1.y)) / ((r->s3.x - r->x) * r->r2.y + (r->x -
	r->s1.x) * r->r1.y);
	r->txtx_bot = (r->u0_bot * repeat[2] * ((r->s3.x - r->x) * r->r2.y) +
	r->u1_bot * repeat[2] * ((r->x - r->s1.x) * r->r1.y)) / ((r->s3.x - r->x) *
	r->r2.y + (r->x - r->s1.x) * r->r1.y);
	r->txtx_top = (r->u0_top * repeat[1] * ((r->s3.x - r->x) * r->r2.y) +
	r->u1_top * repeat[1] * ((r->x - r->s1.x) * r->r1.y)) / ((r->s3.x - r->x)
	* r->r2.y + (r->x - r->s1.x) * r->r1.y);
}

void		draw_transparent_wall3(t_render *r, float *a, int *y, float repeat)
{
	t_wall w;

	w.v1 = r->s.vertexes[r->ii];
	w.v2 = r->s.vertexes[r->ii + 1];
	a[1] = distance_between_point_and_line(r->d->player.position.x,
		r->d->player.position.y, w);
	if (r->s.doors[r->ii])
		repeat = 1;
	y[0] = MAX(r->cya, r->cnya);
	y[0] = CLAMP(y[0], 0, H - 1);
	y[1] = MIN(r->cyb, r->cnyb);
	y[1] = CLAMP(y[1], 0, H - 1);
}

void		draw_transparent_wall2(t_render *r, int y)
{
	int		*pixels;
	int		*texpixels;

	pixels = (int *)r->sdl->screen->pixels;
	texpixels = (int *)r->sdl->wall_texture->pixels;
	if (r->d->transparent_mask[y][r->x] > r->d->dtw)
		r->d->transparent_mask[y][r->x] = r->d->dtw;
	pixels[(int)((y % r->sdl->screen->h) * r->sdl->screen->w +
	(r->x % r->sdl->screen->w))] = apply_shade(texpixels[(int)((r->txty %
	r->sdl->wall_texture->h) * r->sdl->wall_texture->w + (r->txtx %
	r->sdl->wall_texture->w))], r->s.shade);
}

void		draw_transparent_wall(t_render *r)
{
	int		*texpixels;
	int		y[2];
	float	repeat;
	float	alpha_y[2];

	if (r->s.doors[r->ii] && r->s.all_doors[r->i].full_open)
		return ;
	repeat = (r->ceil - r->floor) * 6.4 / r->sdl->wall_texture->h;
	draw_transparent_wall3(r, alpha_y, y, repeat);
	texpixels = (int *)r->sdl->wall_texture->pixels;
	while (++y[0] < y[1])
	{
		if (alpha_y[1] > r->d->transparent_mask[y[0]][r->x])
			continue ;
		alpha_y[0] = (float)((float)(y[0] - r->ya) / (float)(r->yb - r->ya));
		r->txty = alpha_y[0] * r->sdl->wall_texture->h * repeat;
		if (((texpixels[(int)((r->txty %
		r->sdl->wall_texture->h) * r->sdl->wall_texture->w + (r->txtx %
		r->sdl->wall_texture->w))] >> 24) & 0xFF) == 0)
			continue ;
		draw_transparent_wall2(r, y[0]);
	}
}
