/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_stamina_bar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 20:42:43 by dsamarsk          #+#    #+#             */
/*   Updated: 2019/10/13 16:22:52 by dsamarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		init_stamina_bar_param(t_hud *st_bar, t_data *data)
{
	st_bar->p_start = (t_ixy) {.x = 30, .y = 855};
	st_bar->p_end = (t_ixy) {.x = 185, .y = 892};
	st_bar->old_end_x = st_bar->p_end.x;
	st_bar->c = (SDL_Color) {.r = 200, .g = 200, .b = 200};
	st_bar->p_center = (t_ixy)
		{.x = st_bar->p_start.x + ((st_bar->p_end.x - st_bar->p_start.x) / 2),
		.y = st_bar->p_start.y + ((st_bar->p_end.y - st_bar->p_start.y) / 2)};
	st_bar->p_end.x = (st_bar->p_end.x - st_bar->p_start.x) *
						data->player.stamina / 100 + st_bar->p_start.x;
	st_bar->rgb = ((st_bar->c.r & 0xFF) << 16) |
					((st_bar->c.g & 0xFF) << 8) |
							(st_bar->c.b & 0xFF);
}

static void		draw_hud_back_plane(t_hud *st_bar, t_sdl *sdl)
{
	int	back_plane_color;

	back_plane_color = 4934475;
	while (st_bar->p_start.x < st_bar->old_end_x)
	{
		draw_line_on_hud(st_bar->p_start, st_bar->p_end, back_plane_color, sdl);
		st_bar->p_start.x++;
	}
}

static void		draw_hud_front_plane(t_hud *st_bar, t_sdl *sdl)
{
	while (st_bar->p_start.x < st_bar->p_end.x)
	{
		draw_line_on_hud(st_bar->p_start, st_bar->p_end, st_bar->rgb, sdl);
		st_bar->p_start.x++;
	}
}

static void		do_you_exhaust(t_sdl *sdl, t_data *data)
{
	if (sdl->keys.exhaust == true && data->player.stamina <= 33)
		sdl->keys.run = false;
	if (sdl->keys.run == true && sdl->keys.exhaust == false)
		data->player.stamina -=
			data->player.stamina > 0 ? (1 * sdl->difficulty) : (0);
	else
		data->player.stamina +=
			data->player.stamina <= 100 ? (0.6 - sdl->difficulty / 100) : (0);
	if (data->player.stamina <= 0.5)
	{
		sdl->keys.exhaust = true;
		sdl->keys.run = false;
	}
	if (sdl->keys.exhaust == true && data->player.stamina > 33)
		sdl->keys.exhaust = false;
}

void			draw_stamina_bar(t_sdl *sdl, t_data *data)
{
	t_hud		st_bar;
	int			stamina;

	stamina = data->player.stamina;
	do_you_exhaust(sdl, data);
	init_stamina_bar_param(&st_bar, data);
	draw_hud_front_plane(&st_bar, sdl);
	draw_hud_back_plane(&st_bar, sdl);
}
