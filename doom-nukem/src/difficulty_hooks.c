/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   difficulty_hooks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 17:14:50 by dsamarsk          #+#    #+#             */
/*   Updated: 2019/10/16 04:24:27 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	start_game(t_sdl *sdl)
{
	play_game_sound(4, sdl->voice[1], 0, 100);
	ft_bzero(&sdl->keys, sizeof(t_keys));
	sdl->difficulty_loop = false;
	sdl->menu_loop = false;
	sdl->game_started = true;
}

void		choose_difficulty(t_sdl *sdl)
{
	if (sdl->m.key.keysym.sym == SDLK_ESCAPE)
		sdl->difficulty_loop = false;
	if (sdl->m.key.keysym.scancode == SDL_SCANCODE_RETURN)
	{
		if (sdl->active_difficulty_item == 0)
		{
			sdl->difficulty = 1;
			start_game(sdl);
		}
		if (sdl->active_difficulty_item == 1)
		{
			sdl->difficulty = 2;
			start_game(sdl);
		}
		if (sdl->active_difficulty_item == 2)
		{
			sdl->difficulty = 3;
			start_game(sdl);
		}
		if (sdl->active_difficulty_item == 3)
			sdl->difficulty_loop = false;
	}
}
