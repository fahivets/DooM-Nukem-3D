/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_hp_bar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 19:31:56 by dsamarsk          #+#    #+#             */
/*   Updated: 2019/10/13 19:34:33 by dsamarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		init_hp_bar_param(t_hud *hp_bar, t_data *data)
{
	hp_bar->p_start = (t_ixy) {.x = 410, .y = 790};
	hp_bar->p_end = (t_ixy) {.x = 540, .y = 845};
	hp_bar->old_end_x = hp_bar->p_end.x;
	hp_bar->c = (SDL_Color) {.r = 255, .g = 0, .b = 0, .a = 0};
	hp_bar->p_center = (t_ixy)
		{.x = hp_bar->p_start.x + ((hp_bar->p_end.x - hp_bar->p_start.x) / 2),
		.y = hp_bar->p_start.y + ((hp_bar->p_end.y - hp_bar->p_start.y) / 2)};
	hp_bar->p_end.x = (hp_bar->p_end.x - hp_bar->p_start.x) *
						data->player.health / 100 + hp_bar->p_start.x;
	hp_bar->c.r = 85 + data->player.health + 70;
	hp_bar->rgb = ((hp_bar->c.r & 0xFF) << 16) |
					((hp_bar->c.g & 0xFF) << 8) |
									(hp_bar->c.b & 0xFF);
}

static void		draw_hud_back_plane(t_hud *hp_bar, t_sdl *sdl)
{
	int	back_plane_color;

	back_plane_color = 4915200;
	while (hp_bar->p_start.x < hp_bar->old_end_x)
	{
		draw_line_on_hud(hp_bar->p_start, hp_bar->p_end, back_plane_color, sdl);
		hp_bar->p_start.x++;
	}
}

static void		draw_hud_front_plane(t_hud *hp_bar, t_sdl *sdl)
{
	while (hp_bar->p_start.x < hp_bar->p_end.x)
	{
		draw_line_on_hud(hp_bar->p_start, hp_bar->p_end, hp_bar->rgb, sdl);
		hp_bar->p_start.x++;
	}
}

void			draw_hp_bar(t_sdl *sdl, t_data *data)
{
	t_hud		hp_bar;
	char		*hp;

	init_hp_bar_param(&hp_bar, data);
	draw_hud_front_plane(&hp_bar, sdl);
	draw_hud_back_plane(&hp_bar, sdl);
	hp = ft_itoa(data->player.health);
	hp_bar.c = (SDL_Color) {.r = 255, .g = 255, .b = 255};
	draw_hud_info(sdl, hp, hp_bar.p_center, hp_bar.c);
	free(hp);
}
