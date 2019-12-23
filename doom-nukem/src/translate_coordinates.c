/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_coordinates.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 18:42:41 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/15 17:57:05 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	check_vertex_visible(t_render *r)
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

static void	choose_wall_texture(t_sdl *sdl, t_render *r, t_sector s)
{
	if (s.danger)
		sdl->wall_texture = sdl->lava_wall;
	else if (s.transparent[r->i] && !s.doors[r->i])
		sdl->wall_texture = sdl->transparent_wall;
	else if (s.doors[r->i] && !s.all_doors[r->i].full_open)
		sdl->wall_texture = sdl->door_tex[s.all_doors[r->i].keyid
		- 1][s.all_doors[r->i].frame];
	else
		sdl->wall_texture = sdl->wall_textures[s.textures[r->i]];
}

static void	trans_and_rot_coord2(t_data *d, t_render *r, t_sector s)
{
	r->t1.x = s.vertexes[r->i].x - d->player.position.x;
	r->t1.y = s.vertexes[r->i].y - d->player.position.y;
	r->t2.x = s.vertexes[r->i + 1].x - d->player.position.x;
	r->t2.y = s.vertexes[r->i + 1].y - d->player.position.y;
	r->sl1.x = s.vertexes[r->i].x;
	r->sl1.y = s.vertexes[r->i].y;
	r->sl2.x = s.vertexes[r->i + 1].x;
	r->sl2.y = s.vertexes[r->i + 1].y;
	r->r1.x = r->t1.x * d->player.anglesin - r->t1.y * d->player.anglecos;
	r->r1.y = r->t1.x * d->player.anglecos + r->t1.y * d->player.anglesin;
	r->r2.x = r->t2.x * d->player.anglesin - r->t2.y * d->player.anglecos;
	r->r2.y = r->t2.x * d->player.anglecos + r->t2.y * d->player.anglesin;
}

void		trans_and_rot_coord(t_data *d, t_render *r, t_sector s, t_sdl *sdl)
{
	t_wall	w;

	trans_and_rot_coord2(d, r, s);
	w.v1 = s.vertexes[r->i];
	w.v2 = s.vertexes[r->i + 1];
	if (s.transparent[r->i] || s.doors[r->i])
		d->dtw = distance_between_point_and_line(d->player.position.x,
		d->player.position.y, w);
	r->coef_l = 1;
	r->coef_r = 1;
	r->u0 = 0;
	choose_wall_texture(sdl, r, s);
	r->u1 = sdl->wall_texture->w - 1;
	r->u0_bot = 0;
	r->u1_bot = sdl->bot_wall_texture->w - 1;
	r->u0_top = 0;
	r->u1_top = sdl->top_wall_texture->w - 1;
	check_vertex_visible(r);
}
