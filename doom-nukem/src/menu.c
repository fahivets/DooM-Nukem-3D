/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:02:53 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/16 03:25:12 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		draw_text(t_sdl *sdl, char *string, int i)
{
	SDL_Rect	srcrect;
	SDL_Color	color;
	SDL_Surface	*message;

	color.r = 255;
	color.g = 255;
	color.b = 255;
	if (i == sdl->active_menu_item)
	{
		color.g = 0;
		color.b = 0;
	}
	if (sdl->language == false)
		message = TTF_RenderUTF8_Solid(sdl->game_font, string, color);
	else
		message = TTF_RenderUTF8_Solid(sdl->menu_font, string, color);
	srcrect.x = W / 2 - message->w / 2;
	srcrect.y = H / 2.5 + i * 80;
	srcrect.h = 0;
	srcrect.w = 0;
	SDL_BlitSurface(message, NULL, sdl->screen, &srcrect);
	SDL_FreeSurface(message);
}

static void		print_menu_items(t_sdl *sdl)
{
	if (sdl->language == false)
	{
		if (!sdl->game_started)
			draw_text(sdl, "Start Game", 0);
		else
			draw_text(sdl, "Resume", 0);
		draw_text(sdl, "Options", 1);
		draw_text(sdl, "Exit", 2);
	}
	else
	{
		if (!sdl->game_started)
			draw_text(sdl, "Почати гру", 0);
		else
			draw_text(sdl, "Повернутися", 0);
		draw_text(sdl, "Налаштування", 1);
		draw_text(sdl, "Вихід", 2);
	}
}

void			menu(t_sdl *sdl, t_data *d)
{
	while (sdl->menu_loop)
	{
		difficulty(sdl, d);
		options(sdl, d);
		draw_menu(sdl, d);
		print_menu_items(sdl);
		menu_hooks(sdl, d);
		menu_timer(d);
		SDL_Delay(10);
		if (sdl->menu_loop)
			SDL_UpdateWindowSurface(sdl->win);
		play_menu_sounds(sdl);
	}
}
