/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 13:05:40 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/16 04:18:55 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	draw_sprite2(t_render *r, t_data *d, t_sdl *sdl, int x)
{
	int				y;
	int				*pixels;
	int				*texpixels;
	float			alpha_y;

	texpixels = (int *)sdl->sprite_tex->pixels;
	pixels = (int *)sdl->screen->pixels;
	y = r->cya - 1;
	while (++y < r->cyb)
	{
		if (d->transparent_mask[y][x] < d->sprites[r->i].dtp &&
		d->sprites[r->i].sector != d->player.current_sector)
			continue;
		alpha_y = (float)((float)(y - r->ya) / (float)(r->yb - r->ya));
		r->txty = alpha_y * sdl->sprite_tex->h;
		if (((texpixels[(int)((r->txty % sdl->sprite_tex->h) * sdl->sprite_tex
		->w + (r->txtx % sdl->sprite_tex->w))] >> 24) & 0xFF) == 0)
			continue ;
		pixels[(int)(y * sdl->screen->w + x)] = apply_shade(texpixels[(int)
		((r->txty % sdl->sprite_tex->h) * sdl->sprite_tex->w + (r->txtx %
		sdl->sprite_tex->w))], d->sectors[d->sprites[r->i].sector].shade);
	}
}

static void	draw_sprite(t_render *r, t_data *d, t_sdl *sdl, int cs)
{
	int				x;

	r->beginx = MAX(r->s1.x, 0);
	r->endx = MIN(r->s3.x, W - 1);
	x = r->beginx - 1;
	while (++x < r->endx + 1)
	{
		if (!d->left_x[cs][x] && cs != d->player.current_sector)
			continue ;
		r->txtx = (r->u0 * ((r->s3.x - x) * r->r2.y) + r->u1 * ((x - r->s1.x)
		* r->r1.y)) / ((r->s3.x - x) * r->r2.y + (x - r->s1.x) * r->r1.y);
		r->ya = (x - r->s1.x) * (r->s3.y - r->s1.y) / (r->s3.x - r->s1.x)
		+ r->s1.y;
		r->yb = (x - r->s1.x) * (r->s4.y - r->s2.y) / (r->s3.x - r->s1.x)
		+ r->s2.y;
		r->cya = MAX(r->ya, d->topline_n[cs][x]);
		r->cyb = MIN(r->yb, d->bottomline_n[cs][x] + 1);
		draw_sprite2(r, d, sdl, x);
	}
}

static void	draw_all_sprites2(t_data *d, t_render *s, int i)
{
	if (d->sprites[i].type == 3 && d->sprites[i].alive && d->sprites[i].dtp < 1)
		pickup_item(d, i);
	s->s = d->sectors[d->sprites[i].sector];
}

void		draw_all_sprites(t_sdl *sdl, t_data *d)
{
	t_render	s;

	calc_distance(d);
	animate_sprite(d, sdl);
	sort_sprites(d);
	s.i = -1;
	while (++s.i < d->sprite_count)
	{
		draw_all_sprites2(d, &s, s.i);
		if (d->rendered_sectors[d->sprites[s.i].sector] == 0 ||
		(d->sprites[s.i].type == 3 && !d->sprites[s.i].alive))
			continue ;
		trans_coord_sprite(d, &s, s.i, sdl);
		if (s.angle_v1 > DEG_35 && s.angle_v2 > DEG_35)
			if (!(check_wall_intersect_with_view_lines(&s)))
				continue ;
		if (s.angle_v1 > DEG_35 || s.angle_v2 > DEG_35)
			clip_sprite(&s, sdl);
		screen_proj_sprite(&s, d, s.i);
		if (s.s1.x >= s.s3.x)
			continue ;
		draw_sprite(&s, d, sdl, d->sprites[s.i].sector);
		if (fabs(s.beginx - (W - s.endx)) < 500)
			d->sprites[s.i].rendered = 1;
	}
}
