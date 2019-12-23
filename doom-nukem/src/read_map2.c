/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:40:28 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/09 17:45:40 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	calc_sprites_in_sector(t_data *d)
{
	int count[d->sector_count];
	int i;
	int j;

	i = -1;
	while (++i < d->sector_count)
	{
		j = -1;
		count[i] = 0;
		while (++j < d->sprite_count)
			if (d->sprites[j].sector == i)
				count[i]++;
		d->sectors[i].sprite_count = count[i];
		if (d->sectors[i].sprite_count > 0)
			d->sectors[i].sprites = (t_sprite **)malloc(sizeof(t_sprite *) *
			d->sectors[i].sprite_count);
	}
}

void		add_sprites_to_sector(t_data *d)
{
	int i;
	int j;
	int c;

	calc_sprites_in_sector(d);
	i = -1;
	while (++i < d->sector_count)
	{
		j = -1;
		c = 0;
		while (++j < d->sprite_count)
			if (d->sprites[j].sector == i)
				d->sectors[i].sprites[c++] = &d->sprites[j];
	}
}
