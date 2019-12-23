/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 21:09:54 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/15 20:01:43 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static t_sprite	*get_attacked_sprite(t_data *d)
{
	t_sprite	*s;
	int			i;
	float		distance;
	int			count;

	distance = 1e10;
	count = 0;
	i = -1;
	while (++i < d->sprite_count)
		if (d->sprites[i].rendered && d->sprites[i].dtp <
		distance && d->sprites[i].alive)
		{
			s = &d->sprites[i];
			distance = d->sprites[i].dtp;
			count++;
		}
	if (count == 0)
		return (NULL);
	return (s);
}

static void		draw_weapon2(t_sdl *sdl, t_data *d, int *x, int *y)
{
	int *pixels;
	int	*texpixels;

	pixels = (int *)sdl->screen->pixels;
	texpixels = (int *)sdl->weapon_tex[d->player.aw][d->weapon_frame]->pixels;
	if (((texpixels[y[1] * sdl->weapon_tex[d->player.aw][d->weapon_frame]->w
	+ x[1]] >> 24) & 0xFF) != 0)
		pixels[(y[0] % sdl->screen->h) * W + (x[0] %
	sdl->screen->w)] = apply_shade(texpixels[(y[1] % sdl->weapon_tex[d->player.
	aw][d->weapon_frame]->h) * sdl->weapon_tex[d->player.aw][d->weapon_frame]
	->w + (x[1] % sdl->weapon_tex[d->player.aw][d->weapon_frame]->w)],
	d->sectors[d->player.current_sector].shade);
	x[0]++;
}

void			draw_weapon(t_sdl *sdl, t_data *d)
{
	int			x[2];
	int			y[2];
	t_sprite	*s;

	if (d->weapon_frame == d->player.weapon[d->player.aw].frames - 1
	&& d->player.attacking)
	{
		s = get_attacked_sprite(d);
		if (s != NULL && s->dtp < d->player.weapon[d->player.aw].range)
			s->damaged = true;
	}
	y[0] = H - sdl->weapon_tex[d->player.aw][d->weapon_frame]->h - 1;
	y[1] = -1;
	while (++y[1] < sdl->weapon_tex[d->player.aw][d->weapon_frame]->h)
	{
		x[1] = -1;
		x[0] = W / 2 - sdl->weapon_tex[d->player.aw]
		[d->weapon_frame]->w / 2 - 1;
		if (d->player.aw == 1)
			x[0] = W / 2 + 50;
		while (++x[1] < sdl->weapon_tex[d->player.aw][d->weapon_frame]->w)
			draw_weapon2(sdl, d, x, y);
		y[0]++;
	}
}
