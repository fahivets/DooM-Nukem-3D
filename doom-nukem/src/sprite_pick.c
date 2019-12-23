/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_pick.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 03:18:43 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/16 04:28:19 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	pickup_item3(t_data *d, int i)
{
	if (d->sprites[i].id == 10)
	{
		d->player.weapon[1].ammo += 30;
		d->sprites[i].alive = 0;
	}
	if (d->sprites[i].id == 11 && !d->player.weapon[1].have)
	{
		d->player.weapon[1].have = true;
		d->player.weapon[1].ammo += 30;
		d->sprites[i].alive = 0;
		d->player.aw = 1;
		d->player.weapon[1].pick_up = true;
	}
}

static void	pickup_item2(t_data *d, int i)
{
	if (d->sprites[i].id == 5 && !d->player.keys[1])
	{
		d->player.keys[1] = true;
		d->sprites[i].alive = 0;
	}
	if (d->sprites[i].id == 6 && !d->player.keys[2])
	{
		d->player.keys[2] = true;
		d->sprites[i].alive = 0;
	}
	if (d->sprites[i].id == 7 && !d->player.keys[3])
	{
		d->player.keys[3] = true;
		d->sprites[i].alive = 0;
	}
	if (d->sprites[i].id == 8 && !d->player.keys[4])
	{
		d->player.keys[4] = true;
		d->sprites[i].alive = 0;
	}
	if (d->sprites[i].id == 9 && !d->player.keys[5])
	{
		d->player.keys[5] = true;
		d->sprites[i].alive = 0;
	}
}

void		pickup_item(t_data *d, int i)
{
	if (d->sprites[i].id == 1 && d->player.armor < 3)
	{
		d->sprites[i].alive = 0;
		d->player.armor++;
	}
	if (d->sprites[i].id == 2 && d->player.health < 100)
	{
		d->sprites[i].alive = 0;
		d->player.health += 30;
		if (d->player.health > 100)
			d->player.health = 100;
	}
	if (d->sprites[i].id == 3 && d->player.medkit < 100)
	{
		d->player.medkit++;
		d->sprites[i].alive = 0;
	}
	if (d->sprites[i].id == 4 && !d->player.keys[0])
	{
		d->player.keys[0] = true;
		d->sprites[i].alive = 0;
	}
	pickup_item2(d, i);
	pickup_item3(d, i);
}
