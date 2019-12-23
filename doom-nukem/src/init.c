/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 22:04:40 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/17 13:44:16 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	init_flags(t_sdl *sdl, t_data *d)
{
	sdl->menu_loop = true;
	sdl->options_loop = false;
	sdl->difficulty_loop = false;
	sdl->game_started = false;
	sdl->show_fps = true;
	sdl->active_menu_item = 0;
	sdl->active_difficulty_item = 0;
	sdl->active_options_item = 0;
	d->player.alive = true;
}

static void	init_weapons(t_data *d)
{
	d->player.weapon[0].have = 1;
	d->player.weapon[0].frames = 3;
	d->player.weapon[0].id = 0;
	d->player.weapon[0].ammo = 1;
	d->player.weapon[0].dmg_count = 100;
	d->player.weapon[0].range = 3;
	d->player.weapon[0].frame_delay = 150;
	d->player.weapon[1].have = 0;
	d->player.weapon[1].frames = 4;
	d->player.weapon[1].id = 1;
	d->player.weapon[1].ammo = 0;
	d->player.weapon[1].dmg_count = 50;
	d->player.weapon[1].range = 20;
	d->player.weapon[1].frame_delay = 100;
}

void		init(t_data *d, t_sdl *sdl)
{
	int i;

	i = -1;
	ft_bzero(d, sizeof(t_data));
	ft_bzero(&sdl->keys, sizeof(t_keys));
	init_flags(sdl, d);
	init_weapons(d);
	d->player.health = 100;
	d->player.stamina = 100.0;
	d->player.jumping = 0;
	d->player.jumpspeed = 0;
	d->player.falling = 0;
	d->player.fallspeed = 0;
	d->player.armor = 0;
	d->player.medkit = 0;
	d->player.attacking = 0;
	d->player.aw = 0;
	sdl->difficulty = -1;
	d->transparent_mask = (float **)malloc(sizeof(float *) * H);
	while (++i < H)
		d->transparent_mask[i] = (float *)malloc(sizeof(float) * W);
	d->topline = (int *)malloc(sizeof(int) * W);
	d->bottomline = (int *)malloc(sizeof(int) * W);
}

static void	init_repeat2(t_data *d)
{
	int i;
	int j;

	j = -1;
	while (++j < d->sector_count)
	{
		i = -1;
		d->rendered_sectors[j] = 0;
		while (++i < W)
		{
			d->left_x[j][i] = 0;
			d->topline_n[j][i] = 0;
			d->bottomline_n[j][i] = H - 1;
		}
	}
	j = -1;
	while (++j < d->sprite_count)
		d->sprites[j].rendered = false;
	i = -1;
	while (++i < H)
	{
		j = -1;
		while (++j < W)
			d->transparent_mask[i][j] = 1e10;
	}
}

void		init_repeat(t_data *d, t_render *r)
{
	int i;

	i = -1;
	while (++i < W)
	{
		d->topline[i] = 0;
		d->bottomline[i] = H - 1;
	}
	r->left_x[d->player.current_sector] = 0;
	r->right_x[d->player.current_sector] = W - 1;
	d->player.taking_lava_damage = false;
	init_repeat2(d);
}
