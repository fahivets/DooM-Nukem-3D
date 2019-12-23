/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 23:33:07 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/15 17:55:36 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	calculate_intersections(t_data *d, int nb)
{
	int		count;
	int		i;
	t_xy	v[4];

	i = -1;
	count = 0;
	v[0].x = d->player.position.x;
	v[0].y = d->player.position.y;
	v[1].x = 1e9;
	v[1].y = 1e8;
	while (++i < d->sectors[nb].wall_count)
	{
		v[2] = d->sectors[nb].vertexes[i];
		v[3] = d->sectors[nb].vertexes[i + 1];
		if (intersection(v, 1))
			count++;
	}
	return (count);
}

void		update_sector(t_data *d)
{
	int			i;
	t_sector	s;

	s = d->sectors[d->player.current_sector];
	i = -1;
	while (++i < s.wall_count)
		if (s.neighbors[i] >= 0)
			if (calculate_intersections(d, s.neighbors[i]) % 2 != 0)
			{
				d->player.current_sector = s.neighbors[i];
				return ;
			}
}

static int	calculate_intersections_sprite(t_data *d, int nb, int k)
{
	int		count;
	int		i;
	t_xy	v[4];

	i = -1;
	count = 0;
	v[0].x = d->sprites[k].position.x;
	v[0].y = d->sprites[k].position.y;
	v[1].x = 1e9;
	v[1].y = 1e8;
	while (++i < d->sectors[nb].wall_count)
	{
		v[2] = d->sectors[nb].vertexes[i];
		v[3] = d->sectors[nb].vertexes[i + 1];
		if (intersection(v, 1))
			count++;
	}
	return (count);
}

void		update_sprite_sector(t_data *d, int i)
{
	int			j;
	t_sector	s;

	s = d->sectors[d->sprites[i].sector];
	j = -1;
	while (++j < s.wall_count)
		if (s.neighbors[j] >= 0 && calculate_intersections_sprite(d,
		s.neighbors[j], i) % 2 != 0)
		{
			d->sprites[i].sector = s.neighbors[j];
			return ;
		}
}
