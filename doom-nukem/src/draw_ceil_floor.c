/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ceil_floor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 19:15:04 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/15 15:18:17 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	get_map_coordinates(int y, t_data *d, t_render *r)
{
	float rtx;
	float rtz;
	float vangle;

	vangle = d->player.vertical_angle;
	if (((H / 2 - y) - vangle * VFOV) == 0)
		r->map.y = r->z * VFOV / 0.01;
	else
		r->map.y = r->z * VFOV / ((H / 2 - y) - vangle * VFOV);
	r->map.x = r->map.y * (W / 2 - r->x) / HFOV;
	rtx = r->map.y * d->player.anglecos + r->map.x * d->player.anglesin;
	rtz = r->map.y * d->player.anglesin - r->map.x * d->player.anglecos;
	r->map.x = rtx + d->player.position.x;
	r->map.y = rtz + d->player.position.y;
}

static void	interpolate_y(t_render *r, t_data *d)
{
	r->ya = (r->x - r->s1.x) * (r->s3.y - r->s1.y) /
	(r->s3.x - r->s1.x) + r->s1.y;
	r->yb = (r->x - r->s1.x) * (r->s4.y - r->s2.y) /
	(r->s3.x - r->s1.x) + r->s2.y;
	r->cya = MAX(r->ya, d->topline[r->x]);
	r->cya = MIN(r->cya, d->bottomline[r->x]);
	r->cyb = MAX(r->yb, d->topline[r->x]);
	r->cyb = MIN(r->cyb, d->bottomline[r->x]);
}

static void	draw_ceil(t_render *r, t_data *d, t_sdl *sdl, SDL_Surface *ceil)
{
	int		y;
	int		*pixels;
	int		*texpixels;

	pixels = (int *)sdl->screen->pixels;
	texpixels = (int *)ceil->pixels;
	y = d->topline[r->x] - 1;
	r->z = r->ceil;
	while (++y < r->cya)
	{
		if (r->s.skybox || r->d->transparent_mask[y][r->x] != 1e10)
			continue ;
		if (r->ss.slope)
		{
			pixels[(int)((y % sdl->screen->h) * sdl->screen->w + (r->x %
		sdl->screen->w))] = apply_shade(0x414141, r->s.shade);
			continue ;
		}
		get_map_coordinates(y, d, r);
		r->uv.x = (r->map.x * 64);
		r->uv.y = (r->map.y * 64);
		pixels[(int)((y % sdl->screen->h) * sdl->screen->w + (r->x %
		sdl->screen->w))] = apply_shade(texpixels[(int)((r->uv.y % ceil->h)
		* ceil->w + (r->uv.x % ceil->w))], r->s.shade);
	}
}

static void	draw_floor(t_render *r, t_data *d, t_sdl *sdl, SDL_Surface *floor)
{
	int	y;
	int	*pixels;
	int	*texpixels;

	pixels = (int *)sdl->screen->pixels;
	texpixels = (int *)floor->pixels;
	y = r->cyb - 1;
	r->z = r->floor;
	while (++y < d->bottomline[r->x])
	{
		if (r->d->transparent_mask[y][r->x] != 1e10)
			continue ;
		if (r->ss.slope)
		{
			pixels[(int)((y % sdl->screen->h) * sdl->screen->w + (r->x %
		sdl->screen->w))] = apply_shade(0x452004, r->s.shade);
			continue ;
		}
		get_map_coordinates(y, d, r);
		r->uv.x = (r->map.x * 64);
		r->uv.y = (r->map.y * 64);
		pixels[(int)((y % sdl->screen->h) * sdl->screen->w + (r->x %
		sdl->screen->w))] = apply_shade(texpixels[(int)((r->uv.y % floor->h)
		* floor->w + (r->uv.x % floor->w))], r->s.shade);
	}
}

void		draw_floor_ceil(t_render *r, t_data *d, t_sdl *sdl)
{
	SDL_Surface *floor;
	SDL_Surface *ceil;

	if (r->ss.danger)
	{
		floor = sdl->lava_floor[d->lava_frame];
		ceil = sdl->lava_ceil;
	}
	else
	{
		floor = sdl->floor_texture;
		ceil = sdl->ceil_texture;
	}
	interpolate_y(r, d);
	draw_ceil(r, d, sdl, ceil);
	draw_floor(r, d, sdl, floor);
}
