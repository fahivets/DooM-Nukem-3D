/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 17:44:39 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/15 21:32:14 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	key_events4(t_sdl *sdl)
{
	if (sdl->m.key.keysym.sym == SDLK_ESCAPE)
	{
		if (sdl->game_started == true)
		{
			ft_bzero(&sdl->keys, sizeof(t_keys));
			sdl->menu_loop = false;
		}
		else
		{
			sdl->menu_loop = false;
			sdl_close(sdl);
		}
	}
}

static void	key_events3(t_sdl *sdl, t_data *d)
{
	if (sdl->active_menu_item == 0)
	{
		if (sdl->difficulty == -1)
		{
			sdl->difficulty_loop = true;
			sdl->active_difficulty_item = 0;
		}
		else
		{
			ft_bzero(&sdl->keys, sizeof(t_keys));
			sdl->menu_loop = false;
			sdl->game_started = true;
			d->player.vertical_angle = 0;
		}
	}
	if (sdl->active_menu_item == 1)
	{
		sdl->options_loop = true;
		sdl->active_options_item = 0;
	}
	if (sdl->active_menu_item == 2)
	{
		sdl->menu_loop = false;
		sdl_close(sdl);
	}
}

static void	key_events2(t_sdl *sdl)
{
	if (sdl->m.key.keysym.scancode == 22 || sdl->m.key.keysym.sym == SDLK_DOWN)
	{
		play_key_sound(1, sdl->key_sound[1], 0, 100);
		sdl->active_menu_item++;
		if (sdl->active_menu_item >= MENU_ITEMS_COUNT)
			sdl->active_menu_item = 0;
	}
	if (sdl->m.key.keysym.scancode == 26 || sdl->m.key.keysym.sym == SDLK_UP)
	{
		play_key_sound(1, sdl->key_sound[1], 0, 100);
		sdl->active_menu_item--;
		if (sdl->active_menu_item < 0)
			sdl->active_menu_item = MENU_ITEMS_COUNT - 1;
	}
	key_events4(sdl);
}

static void	key_events(t_sdl *sdl, t_data *d)
{
	if (sdl->m.key.keysym.scancode == SDL_SCANCODE_RETURN)
	{
		play_key_sound(1, sdl->key_sound[0], 0, 80);
		key_events3(sdl, d);
	}
	key_events2(sdl);
}

void		menu_hooks(t_sdl *sdl, t_data *d)
{
	while (SDL_PollEvent(&sdl->m))
	{
		if (sdl->m.type == SDL_KEYDOWN)
			key_events(sdl, d);
		if (sdl->m.type == SDL_QUIT)
			sdl_close(sdl);
	}
}
