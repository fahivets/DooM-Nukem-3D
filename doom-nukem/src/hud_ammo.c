/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_ammo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 19:50:16 by dsamarsk          #+#    #+#             */
/*   Updated: 2019/10/15 21:15:56 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		draw_ammo_info(t_sdl *sdl, char *str,
								t_ixy pos, SDL_Color color)
{
	SDL_Rect	srcrect;
	SDL_Surface	*message;

	message = TTF_RenderUTF8_Solid(sdl->hud_ammo_font, str, color);
	srcrect = (SDL_Rect) {.x = pos.x - message->w,
						.y = pos.y - message->h / 2, .w = 0, .h = 0};
	SDL_BlitSurface(message, NULL, sdl->screen, &srcrect);
	SDL_FreeSurface(message);
}

static void		init_ammo_param(t_hud *ammo)
{
	ammo->p_start = (t_ixy) {.x = 1060, .y = 790};
	ammo->p_end = (t_ixy) {.x = 1190, .y = 845};
	ammo->c = (SDL_Color) {.r = 50, .g = 50, .b = 200, .a = 50};
	ammo->p_center = (t_ixy)
		{.x = ammo->p_start.x + ((ammo->p_end.x - ammo->p_start.x) / 2),
		.y = ammo->p_start.y + ((ammo->p_end.y - ammo->p_start.y) / 2)};
}

static void		init_ammo_panel_param(t_hud *all_ammo, t_ixy *plus)
{
	all_ammo->p_start = (t_ixy) {.x = 668 + plus->x, .y = 803 + plus->y};
	all_ammo->p_end = (t_ixy) {.x = 728 + plus->x, .y = 825 + plus->y};
	all_ammo->c = (SDL_Color) {.r = 50, .g = 50, .b = 200, .a = 50};
	all_ammo->p_center = (t_ixy)
		{.x = all_ammo->p_end.x,
		.y = all_ammo->p_end.y -
		((all_ammo->p_end.y - all_ammo->p_start.y) / 2)};
}

void			draw_ammo_panel(t_sdl *sdl, t_data *data)
{
	t_hud		all_ammo[10];
	char		*all_ammo_count;
	int			w_id;
	t_ixy		plus;

	plus = (t_ixy) {.x = 0, .y = 0};
	w_id = 0;
	while (++w_id < 10)
	{
		all_ammo_count =
			ft_itoa(data->player.weapon[w_id].ammo);
		init_ammo_panel_param(&all_ammo[w_id], &plus);
		plus.y += 30;
		if (w_id % 3 == 0)
		{
			plus.x += 114;
			plus.y -= 90;
		}
		draw_ammo_info(sdl, all_ammo_count,
						all_ammo[w_id].p_center, all_ammo[w_id].c);
		free(all_ammo_count);
	}
}

void			draw_active_ammo(t_sdl *sdl, t_data *data)
{
	t_hud		ammo;
	char		*ammo_count;

	if (!data->player.aw)
		ammo_count = ft_itoa(data->player.weapon[data->player.aw].ammo - 1);
	else
		ammo_count = ft_itoa(data->player.weapon[data->player.aw].ammo);
	init_ammo_param(&ammo);
	draw_hud_info(sdl, ammo_count, ammo.p_center, ammo.c);
	free(ammo_count);
}
