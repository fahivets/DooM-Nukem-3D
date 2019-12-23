/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 18:15:02 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/16 22:34:36 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	open_door(t_data *d)
{
	int		i;
	t_wall	w;

	i = -1;
	while (++i < d->sectors[d->player.current_sector].wall_count)
	{
		if (d->sectors[d->player.current_sector].doors[i])
		{
			w.v1 = d->sectors[d->player.current_sector].vertexes[i];
			w.v2 = d->sectors[d->player.current_sector].vertexes[i + 1];
			if (distance_between_point_and_line(d->player.position.x,
			d->player.position.y, w) < 4 && d->player.keys[d->sectors
			[d->player.current_sector].all_doors[i].keyid - 1])
			{
				d->sectors[d->player.current_sector].all_doors[i].openned = 1;
				d->player.keys[d->sectors[d->player.current_sector].
				all_doors[i].keyid - 1] = false;
			}
		}
	}
}

static void	key_events2(t_sdl *sdl, t_data *d)
{
	if (sdl->e.key.keysym.scancode == SDL_SCANCODE_M && d->player.medkit &&
	d->player.health != 100)
	{
		d->player.health = 100;
		d->player.medkit--;
	}
	if (sdl->e.key.keysym.scancode == SDL_SCANCODE_F)
		open_door(d);
	if (sdl->e.key.keysym.scancode == SDL_SCANCODE_1 && !d->player.attacking)
		d->player.aw = 0;
	if (sdl->e.key.keysym.scancode == SDL_SCANCODE_2 &&
	d->player.weapon[1].have && !d->player.attacking)
		d->player.aw = 1;
}

static void	key_events(t_sdl *sdl)
{
	if (sdl->e.key.keysym.scancode == 26 || sdl->e.key.keysym.sym == SDLK_UP)
		sdl->keys.moveup = sdl->e.type == SDL_KEYDOWN;
	if (sdl->e.key.keysym.scancode == 22 || sdl->e.key.keysym.sym == SDLK_DOWN)
		sdl->keys.movedown = sdl->e.type == SDL_KEYDOWN;
	if (sdl->e.key.keysym.scancode == 4 || sdl->e.key.keysym.sym == SDLK_LEFT)
		sdl->keys.moveleft = sdl->e.type == SDL_KEYDOWN;
	if (sdl->e.key.keysym.scancode == 7 || sdl->e.key.keysym.sym == SDLK_RIGHT)
		sdl->keys.moveright = sdl->e.type == SDL_KEYDOWN;
	if (sdl->e.key.keysym.scancode == SDL_SCANCODE_Z)
		sdl->keys.sit = sdl->e.type == SDL_KEYDOWN;
	if (sdl->e.key.keysym.scancode == SDL_SCANCODE_SPACE)
		sdl->keys.jump = sdl->e.type == SDL_KEYDOWN;
	if (sdl->e.key.keysym.scancode == SDL_SCANCODE_LSHIFT)
		sdl->keys.run = sdl->e.type == SDL_KEYDOWN;
}

void		key_hooks(t_sdl *sdl, t_data *d)
{
	while (SDL_PollEvent(&sdl->e))
	{
		if (sdl->e.type == SDL_KEYDOWN)
			if (sdl->e.key.keysym.sym == SDLK_ESCAPE)
			{
				sdl->menu_loop = true;
				sdl->active_menu_item = 0;
			}
		if (sdl->e.type == SDL_KEYDOWN || sdl->e.type == SDL_KEYUP)
			key_events(sdl);
		if (sdl->e.type == SDL_KEYDOWN)
			key_events2(sdl, d);
		if (sdl->e.type == SDL_QUIT)
			sdl_close(sdl);
		if (sdl->e.type == SDL_MOUSEBUTTONDOWN)
			if (sdl->e.button.button == SDL_BUTTON_LEFT)
				d->player.attacking = 1;
	}
}
