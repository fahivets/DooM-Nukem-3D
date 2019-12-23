/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 22:50:53 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/15 15:16:49 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			apply_shade(int color, float shade_factor)
{
	int r;
	int g;
	int b;

	r = (int)(((color >> 16) & 0xFF) * 0.1 * shade_factor);
	g = (int)(((color >> 8) & 0xFF) * 0.1 * shade_factor);
	b = (int)((color & 0xFF) * 0.1 * shade_factor);
	return ((r << 16) | (g << 8) | b);
}

void		draw_wall(t_render *r, t_sdl *sdl)
{
	int		*pixels;
	int		*texpixels;
	int		y;
	float	alpha_y;
	float	repeat;

	repeat = (r->ceil - r->floor) * 6.4 / sdl->wall_texture->h;
	texpixels = (int *)sdl->wall_texture->pixels;
	pixels = (int *)sdl->screen->pixels;
	y = r->cya - 1;
	while (++y < r->cyb)
	{
		if (r->d->transparent_mask[y][r->x] != 1e10)
			continue ;
		alpha_y = (float)((float)(y - r->ya) / (float)(r->yb - r->ya));
		r->txty = alpha_y * sdl->wall_texture->h * repeat;
		if (((texpixels[(int)((r->txty %
		sdl->wall_texture->h) * sdl->wall_texture->w + (r->txtx %
		sdl->wall_texture->w))] >> 24) & 0xFF) == 0)
			continue ;
		pixels[(int)((y % sdl->screen->h) * sdl->screen->w +
		(r->x % sdl->screen->w))] = apply_shade(texpixels[(int)((r->txty %
		sdl->wall_texture->h) * sdl->wall_texture->w + (r->txtx %
		sdl->wall_texture->w))], r->s.shade);
	}
}

static void	manage_next_sector(t_render *r, t_data *d, t_sdl *sdl)
{
	int k;

	k = r->beginx - 1;
	while (++k < r->endx)
		d->left_x[r->ss.neighbors[r->i]][k] = 1;
	r->left_x[r->ss.neighbors[r->i]] = r->beginx;
	r->right_x[r->ss.neighbors[r->i]] = r->endx;
	draw_screen(sdl, r, d, r->ss.neighbors[r->i]);
}

static void	draw_segment(t_render *r, t_data *d, t_sdl *sdl, int cs)
{
	int			j;
	t_render	tmp[THREADS_C];

	j = -1;
	r->beginx = MAX(r->s1.x, r->left_x[cs]);
	r->endx = MIN(r->s3.x, r->right_x[cs]);
	r->beginx = CLAMP(r->beginx, 0, W - 1);
	r->endx = CLAMP(r->endx, 0, W - 1);
	while (++j < THREADS_C)
		tmp[j] = *r;
	manage_treads(r, tmp, sdl, d);
	j = -1;
	while (++j < THREADS_C)
		pthread_create(&sdl->tr[j], NULL, tread, (void *)&tmp[j]);
	j = -1;
	while (++j < THREADS_C)
		pthread_join(sdl->tr[j], NULL);
	if (r->ss.neighbors[r->i] >= 0 && r->endx >= r->beginx)
		manage_next_sector(r, d, sdl);
}

void		draw_screen(t_sdl *sdl, t_render *r, t_data *d, int cs)
{
	t_sector	s;
	int			i;

	i = -1;
	if (d->rendered_sectors[cs] % 2)
		return ;
	++d->rendered_sectors[cs];
	s = d->sectors[cs];
	while (++i < s.wall_count)
	{
		r->i = i;
		trans_and_rot_coord(d, r, s, sdl);
		if (r->angle_v1 > DEG_35 && r->angle_v2 > DEG_35)
			if (!(check_wall_intersect_with_view_lines(r)))
				continue ;
		if (r->angle_v1 > DEG_35 || r->angle_v2 > DEG_35)
			clip_wall(r, s, sdl);
		screen_proj(r, d, s);
		if (r->s1.x >= r->s3.x || r->s3.x < r->left_x[cs] ||
		r->s1.x > r->right_x[cs])
			continue ;
		r->ss = s;
		draw_segment(r, d, sdl, cs);
	}
	++d->rendered_sectors[cs];
}
