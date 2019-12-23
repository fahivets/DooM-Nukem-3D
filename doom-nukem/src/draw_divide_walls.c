/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_divide_walls.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 18:40:22 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/14 19:37:48 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	draw_top_divide_wall(int y1, int y2, t_sdl *sdl, t_render *r)
{
	int		*pixels;
	int		*texpixels;
	int		y;
	float	alpha_y;
	float	repeat;

	repeat = fabs(r->ceil - r->nbceil) * 6.4 / sdl->top_wall_texture->h;
	texpixels = (int *)sdl->top_wall_texture->pixels;
	pixels = (int *)sdl->screen->pixels;
	y = y1 - 1;
	while (++y < y2)
	{
		if (r->d->transparent_mask[y][r->x] != 1e10)
			continue ;
		alpha_y = (float)((float)(y - r->ya) / (float)(r->nya - r->ya));
		r->txty = alpha_y * sdl->top_wall_texture->h * repeat;
		pixels[(int)((y % sdl->screen->h) * sdl->screen->w + (r->x %
		sdl->screen->w))] = apply_shade(texpixels[(int)((r->txty %
		sdl->top_wall_texture->h) * sdl->top_wall_texture->w +
		(r->txtx_top % sdl->top_wall_texture->w))], r->s.shade);
	}
}

static void	draw_bot_divide_wall(int y1, int y2, t_sdl *sdl, t_render *r)
{
	int		*pixels;
	int		*texpixels;
	int		y;
	float	alpha_y;
	float	repeat;

	repeat = fabs(r->floor - r->nbfloor) * 6.4 / sdl->bot_wall_texture->h;
	texpixels = (int *)sdl->bot_wall_texture->pixels;
	pixels = (int *)sdl->screen->pixels;
	y = y1 - 1;
	while (++y < y2)
	{
		if (r->d->transparent_mask[y][r->x] != 1e10)
			continue ;
		alpha_y = (float)((float)(y - r->nyb) /
		(float)(r->yb - r->nyb));
		r->txty = alpha_y * sdl->bot_wall_texture->h * repeat;
		pixels[(int)((y % sdl->screen->h) * sdl->screen->w + (r->x %
		sdl->screen->w))] = apply_shade(texpixels[(int)((r->txty %
		sdl->bot_wall_texture->h) * sdl->bot_wall_texture->w +
		(r->txtx_bot % sdl->bot_wall_texture->w))], r->s.shade);
	}
}

void		draw_divide_walls(t_render *r, t_data *d, t_sdl *sdl, int nb)
{
	draw_top_divide_wall(r->cya, r->cnya, sdl, r);
	draw_bot_divide_wall(r->cnyb, r->cyb, sdl, r);
	d->topline[r->x] = CLAMP(MAX(r->cya, r->cnya), d->topline[r->x], H - 1);
	d->bottomline[r->x] = CLAMP(MIN(r->cyb, r->cnyb), 0, d->bottomline[r->x]);
	d->topline_n[nb][r->x] = MAX(r->cya, r->nya);
	d->bottomline_n[nb][r->x] = MIN(r->cyb, r->nyb);
}
