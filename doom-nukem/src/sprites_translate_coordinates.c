/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_translate_coordinates.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 21:39:08 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/15 17:30:34 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	check_vertex_visible_sprite(t_render *r)
{
	float vector1len;
	float vector2len;
	float normty1;
	float normty2;

	vector1len = sqrt(r->r1.x * r->r1.x + r->r1.y * r->r1.y);
	vector2len = sqrt(r->r2.x * r->r2.x + r->r2.y * r->r2.y);
	normty1 = r->r1.y / vector1len;
	normty2 = r->r2.y / vector2len;
	r->angle_v1 = acosf(normty1);
	r->angle_v2 = acosf(normty2);
}

static void	trans_coord_sprite3(t_data *d, t_render *r, t_sdl *sdl)
{
	r->r1.x = r->t1.x * d->player.anglesin - r->t1.y * d->player.anglecos;
	r->r1.y = r->t1.x * d->player.anglecos + r->t1.y * d->player.anglesin;
	r->r2.x = r->t2.x * d->player.anglesin - r->t2.y * d->player.anglecos;
	r->r2.y = r->t2.x * d->player.anglecos + r->t2.y * d->player.anglesin;
	r->u0 = 0;
	r->u1 = sdl->sprite_tex->w - 1;
	check_vertex_visible_sprite(r);
}

void		trans_coord_sprite2(t_data *d, t_render *r, int i, float *tmp)
{
	tmp[2] = (r->t1.x + r->t2.x) / 2;
	tmp[3] = (r->t1.y + r->t2.y) / 2;
	tmp[6] = (d->sprites[i].v1.x + d->sprites[i].v2.x) / 2;
	tmp[7] = (d->sprites[i].v1.y + d->sprites[i].v2.y) / 2;
	tmp[0] = r->t1.x;
	tmp[1] = r->t2.x;
	tmp[4] = d->sprites[i].v1.x;
	tmp[5] = d->sprites[i].v2.x;
	r->t1.x = ((r->t1.x - tmp[2]) * d->player.anglecos - (r->t1.y -
	tmp[3]) * d->player.anglesin) + tmp[2];
	r->t1.y = ((tmp[0] - tmp[2]) * d->player.anglesin + (r->t1.y -
	tmp[3]) * d->player.anglecos) + tmp[3];
	r->t2.x = ((r->t2.x - tmp[2]) * d->player.anglecos - (r->t2.y -
	tmp[3]) * d->player.anglesin) + tmp[2];
	r->t2.y = ((tmp[1] - tmp[2]) * d->player.anglesin + (r->t2.y -
	tmp[3]) * d->player.anglecos) + tmp[3];
	d->sprites[i].v1.x = ((d->sprites[i].v1.x - tmp[6]) * d->player.anglecos -
	(d->sprites[i].v1.y - tmp[7]) * d->player.anglesin) + tmp[6];
	d->sprites[i].v1.y = ((tmp[4] - tmp[6]) * d->player.anglesin + (d->sprites
	[i].v1.y - tmp[7]) * d->player.anglecos) + tmp[7];
	d->sprites[i].v2.x = ((d->sprites[i].v2.x - tmp[6]) * d->player.anglecos -
	(d->sprites[i].v2.y - tmp[7]) * d->player.anglesin) + tmp[6];
	d->sprites[i].v2.y = ((tmp[5] - tmp[6]) * d->player.anglesin + (d->sprites
	[i].v2.y - tmp[7]) * d->player.anglecos) + tmp[7];
}

void		trans_coord_sprite(t_data *d, t_render *r, int i, t_sdl *sdl)
{
	float tmp[8];

	choose_sprite_texture(sdl, d, i);
	r->t1.x = d->sprites[i].position.x - d->player.position.x;
	r->t1.y = d->sprites[i].position.y - d->sprites[i].w / 20 -
	d->player.position.y;
	r->t2.x = d->sprites[i].position.x - d->player.position.x;
	r->t2.y = d->sprites[i].position.y + d->sprites[i].w / 20 -
	d->player.position.y;
	d->sprites[i].v1.x = d->sprites[i].position.x;
	d->sprites[i].v1.y = d->sprites[i].position.y - d->sprites[i].w / 20;
	d->sprites[i].v2.x = d->sprites[i].position.x;
	d->sprites[i].v2.y = d->sprites[i].position.y + d->sprites[i].w / 20;
	trans_coord_sprite2(d, r, i, tmp);
	trans_coord_sprite3(d, r, sdl);
}
