/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:27:32 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/16 14:47:08 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	move_direction(t_sdl *sdl, t_data *d)
{
	if ((sdl->keys.moveup | sdl->keys.movedown | sdl->keys.moveleft |
				sdl->keys.moveright) && !d->player.jumping)
		play_game_sound(0, sdl->steps, 0, 100);
	else
		Mix_HaltChannel(0);
	if (sdl->keys.moveup)
	{
		d->player.dx += d->player.anglecos * d->player.movespeed;
		d->player.dy += d->player.anglesin * d->player.movespeed;
	}
	if (sdl->keys.movedown)
	{
		d->player.dx += -d->player.anglecos * d->player.movespeed;
		d->player.dy += -d->player.anglesin * d->player.movespeed;
	}
	if (sdl->keys.moveleft)
	{
		d->player.dx += d->player.anglesin * d->player.movespeed;
		d->player.dy += -d->player.anglecos * d->player.movespeed;
	}
	if (sdl->keys.moveright)
	{
		d->player.dx += -d->player.anglesin * d->player.movespeed;
		d->player.dy += d->player.anglecos * d->player.movespeed;
	}
}

void	calc_move_speed(t_sdl *sdl, t_data *d)
{
	d->player.movespeed = 0.2;
	if (sdl->keys.run && !sdl->keys.sit)
		d->player.movespeed *= 1.3;
}

void	sitting(t_sdl *sdl, t_data *d)
{
	if (!d->player.jumping && !sdl->keys.sit)
		d->player.height = PLAYERZ;
	if (sdl->keys.sit && d->player.position.z > d->sectors[d->player.
	current_sector].floor + 4 && !d->player.jumping && !d->player.falling)
		d->player.position.z -= GRAVITATION * 5;
}

void	sprites_z_pos(t_data *d)
{
	int i;

	i = -1;
	while (++i < d->sprite_count)
	{
		d->sprites[i].position.z = d->sectors[d->sprites[i].sector].floor;
		if (d->sectors[d->sprites[i].sector].slope)
			d->sprites[i].position.z = d->sectors[d->sprites[i].sector].floor
		+ calc_slope_h_sprite(d->sectors[d->sprites[i].sector], d->sprites[i]);
	}
}
