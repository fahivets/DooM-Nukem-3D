/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_items.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 19:36:05 by dsamarsk          #+#    #+#             */
/*   Updated: 2019/10/14 15:34:46 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		init_medkit_param(t_hud *medkit)
{
	medkit->p_start = (t_ixy) {.x = 1280, .y = 745};
	medkit->p_end = (t_ixy) {.x = 1373, .y = 885};
	medkit->c = (SDL_Color) {.r = 255, .g = 0, .b = 0, .a = 0};
	medkit->p_center = (t_ixy)
		{.x = medkit->p_start.x + ((medkit->p_end.x - medkit->p_start.x) / 2),
		.y = medkit->p_start.y + ((medkit->p_end.y - medkit->p_start.y) / 6)};
	medkit->rgb = ((medkit->c.r & 0xFF) << 16) |
					((medkit->c.g & 0xFF) << 8) |
									(medkit->c.b & 0xFF);
}

static void		draw_medkit(t_sdl *sdl, t_data *data)
{
	t_hud		items;
	char		*count;
	SDL_Rect	medkit;
	SDL_Rect	screen_plane;

	init_medkit_param(&items);
	screen_plane = (SDL_Rect) {.x = 1280, .y = 885 - sdl->medkit_hud->h};
	medkit = (SDL_Rect) {.x = 0, .y = 0,
							.w = sdl->medkit_hud->w, .h = sdl->medkit_hud->h};
	SDL_BlitSurface(sdl->medkit_hud, &medkit, sdl->screen, &screen_plane);
	count = ft_itoa(data->player.medkit);
	items.c = (SDL_Color) {.r = 150, .g = 0, .b = 0};
	draw_hud_info(sdl, count, items.p_center, items.c);
	free(count);
}

static void		draw_armor(t_sdl *sdl, t_data *data)
{
	t_ixy		plus;
	SDL_Rect	armor_bar;
	SDL_Rect	screen_plane;
	int			armor_count;

	plus = (t_ixy) {.x = 0, .y = 0};
	armor_count = data->player.armor;
	while (armor_count != 0)
	{
		plus.y = 40 * (3 - armor_count);
		screen_plane = (SDL_Rect) {.x = 225, .y = 776 + plus.y};
		armor_bar = (SDL_Rect) {.x = 0, .y = 0,
							.w = sdl->armor_bar->w, .h = sdl->armor_bar->h};
		SDL_BlitSurface(sdl->armor_bar, &armor_bar,
						sdl->screen, &screen_plane);
		armor_count--;
	}
}

void			draw_hud_items(t_sdl *sdl, t_data *data)
{
	draw_medkit(sdl, data);
	draw_keys(sdl, data);
	draw_armor(sdl, data);
}
