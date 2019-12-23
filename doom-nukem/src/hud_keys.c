/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 22:14:33 by dsamarsk          #+#    #+#             */
/*   Updated: 2019/10/13 22:16:25 by dsamarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		if_key_false(t_sdl *sdl, int key_id, t_ixy *plus)
{
	SDL_Rect	key_false;
	SDL_Rect	screen_plane;

	if (key_id > 0)
		plus->y += 56;
	if (key_id % 3 == 0 && key_id != 0)
	{
		plus->x += 863;
		plus->y -= 168;
	}
	screen_plane = (SDL_Rect) {.x = 345 + plus->x, .y = 734 + plus->y};
	key_false = (SDL_Rect) {.x = 0, .y = 0,
				.w = sdl->key_false[key_id]->w, .h = sdl->key_false[key_id]->h};
	SDL_BlitSurface(sdl->key_false[key_id], &key_false,
					sdl->screen, &screen_plane);
}

static void		if_key_true(t_sdl *sdl, int key_id, t_ixy *plus)
{
	SDL_Rect	key_true;
	SDL_Rect	screen_plane;

	if (key_id > 0)
		plus->y += 56;
	if (key_id % 3 == 0 && key_id != 0)
	{
		plus->x += 863;
		plus->y -= 168;
	}
	screen_plane = (SDL_Rect) {.x = 345 + plus->x, .y = 734 + plus->y};
	key_true = (SDL_Rect) {.x = 0, .y = 0,
				.w = sdl->key_true[key_id]->w, .h = sdl->key_true[key_id]->h};
	SDL_BlitSurface(sdl->key_true[key_id], &key_true,
					sdl->screen, &screen_plane);
}

void			draw_keys(t_sdl *sdl, t_data *data)
{
	t_ixy		plus;
	int			key_id;

	plus = (t_ixy) {.x = 0, .y = 0};
	key_id = -1;
	while (++key_id < 6)
	{
		if (data->player.keys[key_id] == false)
			if_key_false(sdl, key_id, &plus);
		else
			if_key_true(sdl, key_id, &plus);
	}
}
