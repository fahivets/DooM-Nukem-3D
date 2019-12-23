/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 19:45:04 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/15 21:32:24 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	draw_options_text(t_sdl *sdl, char *string, int i)
{
	SDL_Rect	srcrect;
	SDL_Color	color;
	SDL_Surface	*message;

	color.r = 255;
	color.g = 255;
	color.b = 255;
	if (i == sdl->active_options_item)
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

static void	key_events(t_sdl *sdl)
{
	if (sdl->m.key.keysym.scancode == SDL_SCANCODE_RETURN)
	{
		play_key_sound(1, sdl->key_sound[0], 0, 80);
		if (sdl->active_options_item == 0)
			sdl->show_fps = sdl->show_fps == false ? true : false;
		if (sdl->active_options_item == 1)
			sdl->language = sdl->language == false ? true : false;
		if (sdl->active_options_item == 2)
			sdl->options_loop = false;
	}
	if (sdl->m.key.keysym.scancode == 22 || sdl->m.key.keysym.sym == SDLK_DOWN)
	{
		play_key_sound(1, sdl->key_sound[1], 0, 100);
		sdl->active_options_item++;
		if (sdl->active_options_item >= OPTIONS_ITEMS_COUNT)
			sdl->active_options_item = 0;
	}
	if (sdl->m.key.keysym.scancode == 26 || sdl->m.key.keysym.sym == SDLK_UP)
	{
		play_key_sound(1, sdl->key_sound[1], 0, 100);
		sdl->active_options_item--;
		if (sdl->active_options_item < 0)
			sdl->active_options_item = OPTIONS_ITEMS_COUNT - 1;
	}
}

static void	options_hooks(t_sdl *sdl)
{
	while (SDL_PollEvent(&sdl->m))
	{
		if (sdl->m.type == SDL_KEYDOWN)
		{
			if (sdl->m.key.keysym.sym == SDLK_ESCAPE)
				sdl->options_loop = false;
			key_events(sdl);
		}
		if (sdl->m.type == SDL_QUIT)
			sdl_close(sdl);
	}
}

static void	print_options_items(t_sdl *sdl)
{
	if (sdl->language == false)
	{
		if (sdl->show_fps)
			draw_options_text(sdl, "Show FPS: Enabled", 0);
		else
			draw_options_text(sdl, "Show FPS: Disabled", 0);
		draw_options_text(sdl, "Language: English", 1);
		draw_options_text(sdl, "Back", 2);
	}
	else
	{
		if (sdl->show_fps)
			draw_options_text(sdl, "Відображати FPS: Так", 0);
		else
			draw_options_text(sdl, "Відображати FPS: Ніт", 0);
		draw_options_text(sdl, "Мова: Українська", 1);
		draw_options_text(sdl, "Назад", 2);
	}
}

void		options(t_sdl *sdl, t_data *data)
{
	SDL_Rect	srcrect;

	srcrect.x = 0;
	srcrect.y = 0;
	srcrect.w = W;
	srcrect.h = H;
	while (sdl->options_loop)
	{
		SDL_FillRect(sdl->screen, NULL, 0x000000);
		SDL_BlitSurface(sdl->menu_bg, &srcrect, sdl->screen, NULL);
		menu_timer(data);
		draw_menu(sdl, data);
		print_options_items(sdl);
		options_hooks(sdl);
		SDL_UpdateWindowSurface(sdl->win);
		play_menu_sounds(sdl);
	}
}
