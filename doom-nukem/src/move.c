/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 16:41:51 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/16 14:47:03 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	apply_jump(t_data *d)
{
	if ((!d->sectors[d->player.current_sector].slope && d->player.position.z
	+ HEADMARGIN >= d->sectors[d->player.current_sector].ceil &&
	d->player.jumpspeed > 0) || (d->sectors[d->player.current_sector].slope
	&& d->player.position.z + HEADMARGIN >= d->sectors[d->player.
	current_sector].ceil + calc_slope_h(d->sectors[d->player.
	current_sector], d) && d->player.jumpspeed > 0))
		d->player.jumpspeed = 0;
	d->player.height += d->player.jumpspeed;
	d->player.jumpspeed -= GRAVITATION;
	if (d->player.position.z <= d->sectors[d->player.current_sector].floor
	+ PLAYERZ - d->player.jumpspeed - GRAVITATION || (d->sectors[d->player.
	current_sector].slope && d->player.position.z <= d->sectors[d->player.
	current_sector].floor + PLAYERZ - d->player.jumpspeed - GRAVITATION +
	calc_slope_h(d->sectors[d->player.current_sector], d)))
	{
		d->player.position.z = d->sectors[d->player.current_sector].floor
		+ PLAYERZ;
		d->player.jumping = false;
	}
}

static void	jumping(t_sdl *sdl, t_data *d)
{
	if (sdl->keys.jump)
	{
		if (d->player.height == PLAYERZ && !d->player.falling)
		{
			d->player.jumping = true;
			d->player.jumpspeed = 0.5;
			d->player.jumpsector = d->player.current_sector;
		}
	}
	if (d->player.jumping)
		apply_jump(d);
	if (d->player.position.z - PLAYERZ > d->sectors[d->player.current_sector].
	floor && !d->player.jumping && !d->sectors[d->player.current_sector].slope)
		d->player.falling = true;
	else
	{
		d->player.falling = false;
		d->player.fallspeed = 0;
	}
}

static void	apply_move(t_data *d, t_sdl *sdl)
{
	d->player.position.x += d->player.dx;
	d->player.position.y += d->player.dy;
	if (d->player.jumping)
		d->player.position.z = d->sectors[d->player.jumpsector].floor
	+ d->player.height;
	if (d->player.jumping && d->sectors[d->player.jumpsector].slope)
		d->player.position.z = d->sectors[d->player.jumpsector].floor
	+ d->player.height + calc_slope_h(d->sectors[d->player.jumpsector], d);
	if (d->player.falling)
	{
		d->player.position.z += d->player.fallspeed;
		d->player.fallspeed -= GRAVITATION;
	}
	if (d->player.position.z - PLAYERZ < d->sectors[d->player.current_sector].
	floor && !sdl->keys.sit)
		d->player.position.z = d->sectors[d->player.current_sector].floor +
	PLAYERZ;
	if (d->player.position.z - PLAYERZ < d->sectors[d->player.current_sector].
	floor && sdl->keys.sit)
		d->player.position.z = d->sectors[d->player.current_sector].floor + 4;
}

void		move(t_sdl *sdl, t_data *d)
{
	d->player.dx = 0;
	d->player.dy = 0;
	calc_move_speed(sdl, d);
	move_direction(sdl, d);
	sitting(sdl, d);
	jumping(sdl, d);
	sprites_z_pos(d);
	collision(d);
	apply_move(d, sdl);
	update_sector(d);
	slope_move(d);
}
