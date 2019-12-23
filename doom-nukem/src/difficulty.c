/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   difficulty.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 15:05:29 by dsamarsk          #+#    #+#             */
/*   Updated: 2019/10/16 00:17:27 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	draw_difficulty_text(t_sdl *sdl, char *string, int i)
{
	SDL_Rect	srcrect;
	SDL_Color	color;
	SDL_Surface	*message;

	color.r = 255;
	color.g = 255;
	color.b = 255;
	if (i == sdl->active_difficulty_item)
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

static void	difficulty_key_events(t_sdl *sdl)
{
	choose_difficulty(sdl);
	if (sdl->m.key.keysym.scancode == 22 || sdl->m.key.keysym.sym == SDLK_DOWN)
	{
		play_key_sound(1, sdl->key_sound[1], 0, 100);
		sdl->active_difficulty_item++;
		if (sdl->active_difficulty_item >= DIFFICULTY_ITEMS_COUNT)
			sdl->active_difficulty_item = 0;
	}
	if (sdl->m.key.keysym.scancode == 26 || sdl->m.key.keysym.sym == SDLK_UP)
	{
		play_key_sound(1, sdl->key_sound[1], 0, 100);
		sdl->active_difficulty_item--;
		if (sdl->active_difficulty_item < 0)
			sdl->active_difficulty_item = DIFFICULTY_ITEMS_COUNT - 1;
	}
}

static void	difficulty_hooks(t_sdl *sdl)
{
	while (SDL_PollEvent(&sdl->m))
	{
		if (sdl->m.type == SDL_KEYDOWN)
			difficulty_key_events(sdl);
		if (sdl->m.type == SDL_QUIT)
			sdl_close(sdl);
	}
}

static void	print_difficulty_items(t_sdl *sdl)
{
	if (sdl->language == false)
	{
		draw_difficulty_text(sdl, "ucode", 0);
		draw_difficulty_text(sdl, "Mommy's nagibator", 1);
		draw_difficulty_text(sdl, "Fahivets", 2);
		draw_difficulty_text(sdl, "Back", 3);
	}
	else
	{
		draw_difficulty_text(sdl, "юкод", 0);
		draw_difficulty_text(sdl, "Мамин нагібатор", 1);
		draw_difficulty_text(sdl, "Фахівець", 2);
		draw_difficulty_text(sdl, "Назад", 3);
	}
}

void		difficulty(t_sdl *sdl, t_data *data)
{
	SDL_Rect	srcrect;

	srcrect.x = 0;
	srcrect.y = 0;
	srcrect.w = W;
	srcrect.h = H;
	while (sdl->difficulty_loop)
	{
		SDL_FillRect(sdl->screen, NULL,
				SDL_MapRGB(sdl->screen->format, 0, 0, 0));
		SDL_BlitSurface(sdl->menu_bg, &srcrect, sdl->screen, NULL);
		menu_timer(data);
		draw_menu(sdl, data);
		print_difficulty_items(sdl);
		difficulty_hooks(sdl);
		SDL_UpdateWindowSurface(sdl->win);
		play_menu_sounds(sdl);
	}
}
