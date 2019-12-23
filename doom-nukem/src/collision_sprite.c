/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_sprite.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 22:42:41 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/15 15:15:28 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		wall_collision2(t_data *d, int k, float top, float bot)
{
	if (top < d->sprites[k].position.z + d->sprites[k].h ||
	bot > d->sprites[k].position.z + LEG_HEIGHT + 2 ||
	d->sprites[k].position.z + LEG_HEIGHT + 2 > top)
		get_desired_motion(&d->sprite_dx, &d->sprite_dy, d->sprite_w);
}

static void		wall_collision(t_data *d, t_sector s, int j, int k)
{
	float	top;
	float	bot;

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
	wall_collision2(d, k, top, bot);
}

void			collision_sprite(t_data *d, int k)
{
	int			i;
	int			j;
	t_sector	s;

	i = -1;
	while (++i < d->sector_count)
	{
		j = -1;
		s = d->sectors[i];
		while (++j < s.wall_count)
		{
			d->sprite_w.v1 = s.vertexes[j];
			d->sprite_w.v2 = s.vertexes[j + 1];
			if (lci(d->sprites[k].position.x - d->sprite_dx + PLAYERBOX,
			d->sprites[k].position.y - d->sprite_dy, PLAYERBOX, d->sprite_w))
				wall_collision(d, s, j, k);
		}
	}
}
