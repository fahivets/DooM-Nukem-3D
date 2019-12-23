/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 21:03:29 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/17 15:25:05 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		menu_timer(t_data *d)
{
	unsigned int	current_time;

	current_time = SDL_GetTicks();
	if (current_time > d->time_menu_torch + MENU_TORCH_DELAY)
	{
		d->menu_torch_frame++;
		if (d->menu_torch_frame > 3)
			d->menu_torch_frame = 0;
		d->time_menu_torch = current_time;
	}
	if (current_time > d->time_menu_blood + MENU_BLOOD_DELAY)
	{
		d->menu_blood_frame++;
		if (d->menu_blood_frame > 7)
			d->menu_blood_frame = 0;
		d->time_menu_blood = current_time;
	}
}

static void	timer3(t_data *d, t_sector s)
{
	int i;

	i = -1;
	if (d->current_time > d->time_door + DOOR_DELAY)
	{
		while (++i < s.wall_count)
		{
			if (s.all_doors[i].openned)
				s.all_doors[i].frame++;
			if (s.all_doors[i].frame > 4)
			{
				s.all_doors[i].full_open = true;
				s.all_doors[i].frame = 4;
			}
		}
		d->time_door = d->current_time;
	}
}

static void	timer2(t_data *d, t_sdl *sdl, t_sector s)
{
	int i;

	i = -1;
	if (d->current_time > d->time_lava_damage + LAVA_DAMAGE_DELAY)
	{
		while (++i < d->sprite_count)
			if (d->sectors[d->sprites[i].sector].danger &&
				d->sprites[i].alive && d->sprites[i].type == 1)
				d->sprites[i].health -= 3;
		if (s.danger)
		{
			d->player.health -= 3 * sdl->difficulty;
			d->player.taking_lava_damage = true;
			if (d->player.health < 0)
				d->player.health = 0;
		}
		d->time_lava_damage = d->current_time;
	}
}

static void	attack_end(t_data *d)
{
	if (d->player.weapon[d->player.aw].id != 0)
		d->player.weapon[d->player.aw].ammo--;
	if (d->player.weapon[d->player.aw].ammo < 0)
		d->player.weapon[d->player.aw].ammo = 0;
	d->weapon_frame = 0;
	d->player.attacking = 0;
}

void		timers(t_data *d, t_sdl *sdl)
{
	t_sector	s;

	s = d->sectors[d->player.current_sector];
	d->current_time = SDL_GetTicks();
	if (d->player.attacking && d->current_time > d->time_weapon + d->player.
	weapon[d->player.aw].frame_delay)
	{
		if (!d->player.weapon[d->player.aw].ammo)
			d->player.attacking = 0;
		else
		{
			d->weapon_frame++;
			d->time_weapon = d->current_time;
			if (d->weapon_frame > d->player.weapon[d->player.aw].frames - 1)
				attack_end(d);
		}
	}
	if (d->current_time > d->time_lava_floor + LAVA_DELAY)
	{
		d->lava_frame++;
		d->lava_frame = d->lava_frame > 3 ? (0) : (d->lava_frame);
		d->time_lava_floor = d->current_time;
	}
	timer2(d, sdl, s);
	timer3(d, s);
}
