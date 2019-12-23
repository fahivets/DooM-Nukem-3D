/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 19:21:00 by dsamarsk          #+#    #+#             */
/*   Updated: 2019/10/13 19:58:44 by dsamarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			draw_line_on_hud(t_ixy p_start, t_ixy p_end,
										int color, t_sdl *sdl)
{
	int			*pixels;

	pixels = (int *)sdl->screen->pixels;
	while (p_start.y < p_end.y)
	{
		pixels[(int)(p_start.y * sdl->screen->w + p_start.x)] = color;
		p_start.y++;
	}
}

void			draw_hud_info(t_sdl *sdl, char *str, t_ixy pos, SDL_Color color)
{
	SDL_Rect	srcrect;
	SDL_Surface	*message;

	message = TTF_RenderUTF8_Solid(sdl->game_font, str, color);
	srcrect = (SDL_Rect) {.x = pos.x - message->w / 2,
						.y = pos.y - message->h / 2, .w = 0, .h = 0};
	SDL_BlitSurface(message, NULL, sdl->screen, &srcrect);
	SDL_FreeSurface(message);
}

static void		init_hud_param(t_sdl *sdl, t_data *data)
{
	draw_hp_bar(sdl, data);
	draw_stamina_bar(sdl, data);
	draw_active_ammo(sdl, data);
	draw_ammo_panel(sdl, data);
	draw_hud_items(sdl, data);
}

void			draw_hud(t_sdl *sdl, t_data *data)
{
	SDL_Rect	hud_panel;
	SDL_Rect	screen_plane;

	screen_plane = (SDL_Rect) {.x = 0, .y = H - sdl->hud->h};
	hud_panel = (SDL_Rect) {.x = 0, .y = 0,
							.w = sdl->hud->w, .h = sdl->hud->h};
	SDL_BlitSurface(sdl->hud, &hud_panel, sdl->screen, &screen_plane);
	init_hud_param(sdl, data);
}
