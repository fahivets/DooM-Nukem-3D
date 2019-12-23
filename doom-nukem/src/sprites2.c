/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:46:48 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/16 03:18:57 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		calc_distance(t_data *d)
{
	int i;

	i = -1;
	while (++i < d->sprite_count)
	{
		d->sprites[i].dtp = sqrt((d->sprites[i].position.x -
		d->player.position.x) * (d->sprites[i].position.x -
		d->player.position.x) + (d->sprites[i].position.y -
		d->player.position.y) * (d->sprites[i].position.y -
		d->player.position.y));
		if (d->sprites[i].dtp < 3 && d->sprites[i].sector
			== d->player.current_sector)
			d->sprites[i].attack = 1;
	}
}

void		sort_sprites(t_data *d)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = -1;
	while (++i < d->sprite_count - 1)
	{
		j = -1;
		while (++j < d->sprite_count - i - 1)
		{
			if (d->sprites[j].dtp < d->sprites[j + 1].dtp)
			{
				tmp = d->sprites[j];
				d->sprites[j] = d->sprites[j + 1];
				d->sprites[j + 1] = tmp;
			}
		}
	}
}

void		choose_sprite_texture(t_sdl *sdl, t_data *d, int i)
{
	if (d->sprites[i].id == 0)
		sdl->sprite_tex = sdl->doom_mob_tex[d->sprites[i].frame];
	if (d->sprites[i].id == 1)
		sdl->sprite_tex = sdl->armor_tex;
	if (d->sprites[i].id == 2)
		sdl->sprite_tex = sdl->hp_potion_tex;
	if (d->sprites[i].id == 3)
		sdl->sprite_tex = sdl->medkit_tex;
	if (d->sprites[i].id == 4)
		sdl->sprite_tex = sdl->key1;
	if (d->sprites[i].id == 5)
		sdl->sprite_tex = sdl->key2;
	if (d->sprites[i].id == 6)
		sdl->sprite_tex = sdl->key3;
	if (d->sprites[i].id == 7)
		sdl->sprite_tex = sdl->key4;
	if (d->sprites[i].id == 8)
		sdl->sprite_tex = sdl->key5;
	if (d->sprites[i].id == 9)
		sdl->sprite_tex = sdl->key6;
	if (d->sprites[i].id == 10)
		sdl->sprite_tex = sdl->ammo;
	if (d->sprites[i].id == 11)
		sdl->sprite_tex = sdl->pistol;
}
