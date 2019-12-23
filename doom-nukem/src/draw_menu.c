/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:59:09 by dsamarsk          #+#    #+#             */
/*   Updated: 2019/10/15 21:21:28 by dsamarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		draw_menu_blood(t_sdl *sdl, t_data *d)
{
	SDL_Rect	torch[8];
	SDL_Rect	screen_plane;

	screen_plane = (SDL_Rect) {.x = 0, .y = 0 };
	torch[d->menu_blood_frame] = (SDL_Rect) {.x = 0, .y = 0,
			.w = sdl->menu_blood[d->menu_blood_frame]->w,
			.h = sdl->menu_blood[d->menu_blood_frame]->h};
	SDL_BlitSurface(sdl->menu_blood[d->menu_blood_frame],
					&torch[d->menu_blood_frame], sdl->screen, &screen_plane);
}

static void		draw_menu_torch(t_sdl *sdl, t_data *d)
{
	SDL_Rect	torch[4];
	SDL_Rect	screen_plane;

	screen_plane = (SDL_Rect) {.x = 400, .y = 40 };
	torch[d->menu_torch_frame] = (SDL_Rect) {.x = 0, .y = 0,
			.w = sdl->menu_torch[d->menu_torch_frame]->w,
			.h = sdl->menu_torch[d->menu_torch_frame]->h};
	SDL_BlitSurface(sdl->menu_torch[d->menu_torch_frame],
				&torch[d->menu_torch_frame], sdl->screen, &screen_plane);
	screen_plane = (SDL_Rect) {.x = 1100, .y = 40 };
	torch[3 - d->menu_torch_frame] = (SDL_Rect) {.x = 0, .y = 0,
			.w = sdl->menu_torch[3 - d->menu_torch_frame]->w,
			.h = sdl->menu_torch[3 - d->menu_torch_frame]->h};
	SDL_BlitSurface(sdl->menu_torch[3 - d->menu_torch_frame],
				&torch[3 - d->menu_torch_frame], sdl->screen, &screen_plane);
}

static void		draw_menu_bg(t_sdl *sdl)
{
	SDL_Rect	menu_bg;
	SDL_Rect	screen_plane;

	screen_plane = (SDL_Rect) {.x = 0, .y = 0};
	menu_bg = (SDL_Rect) {.x = 0, .y = 0,
							.w = sdl->menu_bg->w, .h = sdl->menu_bg->h};
	SDL_FillRect(sdl->screen, NULL, 0x000000);
	SDL_BlitSurface(sdl->menu_bg, &menu_bg, sdl->screen, &screen_plane);
}

void			draw_menu(t_sdl *sdl, t_data *data)
{
	draw_menu_bg(sdl);
	draw_menu_torch(sdl, data);
	draw_menu_blood(sdl, data);
}
