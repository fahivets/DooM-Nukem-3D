/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_animation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 22:59:33 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/16 04:29:12 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	attack_animation(t_data *d, int i, t_sdl *sdl)
{
	if (d->sprites[i].frame < 4)
		d->sprites[i].frame = 4;
	if (d->sprites[i].frame > 6)
		d->sprites[i].frame = 4;
	if (d->sprites[i].frame == 6)
	{
		if (d->sprites[i].dtp < 5 && d->player.health > 0 &&
		d->sprites[i].alive)
		{
			SDL_FillRect(sdl->screen, NULL, 0x960000);
			if (d->player.armor)
				d->player.armor--;
			else
			{
				d->player.health -= 13 * sdl->difficulty;
				if (d->player.health < 0)
					d->player.health = 0;
			}
		}
		d->sprites[i].attack = 0;
	}
}

static void	damaged_animation(t_data *d, int i, t_sdl *sdl)
{
	if (d->sprites[i].frame < 7)
		d->sprites[i].frame = 7;
	if (d->sprites[i].frame > 8)
		d->sprites[i].frame = 7;
	if (d->sprites[i].frame == 8)
	{
		d->sprites[i].health -= d->player.weapon[d->player.aw].
		dmg_count / sdl->difficulty;
		d->sprites[i].damaged = 0;
	}
}

static void	death_animation(t_data *d, int i)
{
	if (d->sprites[i].frame < 9)
		d->sprites[i].frame = 9;
	if (d->sprites[i].frame > 13)
		d->sprites[i].frame = 9;
	if (d->sprites[i].frame == 13)
	{
		d->sprites[i].h = 3;
		d->sprites[i].alive = 0;
	}
}

static void	animate_sprite2(t_data *d, t_sdl *sdl, int i)
{
	if (d->sprites[i].health <= 0 && d->sprites[i].alive)
	{
		play_game_sound(5, sdl->monster[1], 0, 100);
		death_animation(d, i);
	}
	else if (d->sprites[i].damaged && d->sprites[i].alive)
	{
		play_game_sound(6, sdl->monster[0], 0, 100);
		damaged_animation(d, i, sdl);
	}
	else if (d->sprites[i].attack && d->sprites[i].alive)
		attack_animation(d, i, sdl);
	else if (d->sprites[i].frame > 3 && d->sprites[i].alive &&
	d->sprites[i].dtp < 20)
		d->sprites[i].frame = 0;
}

void		animate_sprite(t_data *d, t_sdl *sdl)
{
	int i;

	i = -1;
	if (d->current_time > d->time_sprite + SPRITE_DELAY)
	{
		while (++i < d->sprite_count)
		{
			if (!d->sprites[i].animated)
				continue ;
			d->sprites[i].frame++;
			if (!d->sprites[i].alive)
				d->sprites[i].frame = 13;
			if (d->sprites[i].dtp > 20 && d->sprites[i].type == 1 && d->sprites
			[i].alive && (d->sprites[i].frame < 9 || d->sprites[i].frame > 13))
				if (d->sprites[i].frame > 16 || d->sprites[i].frame < 14)
					d->sprites[i].frame = 14;
			animate_sprite2(d, sdl, i);
		}
		d->time_sprite = d->current_time;
	}
}
