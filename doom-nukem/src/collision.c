/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:10:42 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/16 18:54:44 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		wall_collision2(t_data *d, float top, float bot, t_wall w)
{
	if (top < d->player.position.z + HEADMARGIN ||
	bot > d->player.position.z - PLAYERZ + LEG_HEIGHT ||
	d->player.position.z - PLAYERZ + LEG_HEIGHT > top)
	{
		get_desired_motion(&d->player.dx, &d->player.dy, w);
		d->player.collision_count++;
	}
}

static void		wall_collision(t_data *d, t_sector s, int j, t_wall w)
{
	float top;
	float bot;

	if (s.neighbors[j] < 0 || (s.transparent[j] && !s.doors[j]) ||
	(s.doors[j] && s.all_doors[j].frame < 4))
	{
		top = -1e10;
		bot = 1e10;
	}
	else
	{
		if (s.slope || d->sectors[s.neighbors[j]].slope)
		{
			top = 1e10;
			bot = -1e10;
		}
		else
		{
			top = MIN(s.ceil, d->sectors[s.neighbors[j]].ceil);
			bot = MAX(s.floor, d->sectors[s.neighbors[j]].floor);
		}
	}
	wall_collision2(d, top, bot, w);
}

static void		sprite_collision(t_data *d)
{
	int		i;
	t_wall	w;

	i = -1;
	while (++i < d->sprite_count)
	{
		if (d->sprites[i].type == 3)
			continue ;
		w.v1 = d->sprites[i].v1;
		w.v2 = d->sprites[i].v2;
		if (lci(d->player.position.x + d->player.dx, d->player.position.y +
		d->player.dy, PLAYERBOX * 2, w) && d->sprites[i].alive)
		{
			get_desired_motion(&d->player.dx, &d->player.dy, w);
			d->player.collision_count++;
		}
	}
	if (d->player.collision_count > 1)
	{
		d->player.dx = 0;
		d->player.dy = 0;
	}
}

void			collision(t_data *d)
{
	int			i;
	int			j;
	t_wall		w;
	t_sector	s;

	d->player.collision_count = 0;
	i = -1;
	while (++i < d->sector_count)
	{
		j = -1;
		s = d->sectors[i];
		while (++j < s.wall_count)
		{
			w.v1 = s.vertexes[j];
			w.v2 = s.vertexes[j + 1];
			if (lci(d->player.position.x + d->player.dx, d->player.position.y +
			d->player.dy, PLAYERBOX, w))
				wall_collision(d, s, j, w);
		}
	}
	sprite_collision(d);
}
