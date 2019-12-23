/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_death.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 03:27:38 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/16 15:21:57 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	win_death_loop2(t_sdl *sdl, int *i, SDL_Rect src, SDL_Surface *msg)
{
	int			*pixels;

	pixels = (int *)sdl->screen->pixels;
	i[1] = -1;
	while (++i[1] < H)
	{
		i[0] = -1;
		while (++i[0] < W)
			pixels[i[1] * sdl->screen->w + i[0]] =
		apply_shade(pixels[i[1] * sdl->screen->w + i[0]], 7);
	}
	if (i[2] > 8)
		SDL_BlitSurface(msg, NULL, sdl->screen, &src);
	SDL_Delay(300);
	SDL_UpdateWindowSurface(sdl->win);
}

static void	win_death_loop(t_sdl *sdl, int l)
{
	int			i[3];
	SDL_Surface	*msg;
	SDL_Rect	src;
	SDL_Color	c;

	c = (SDL_Color) {.r = 255, .b = 0, .g = 0 };
	if (l == 1)
		msg = TTF_RenderUTF8_Solid(sdl->game_font, "YOU WIN", c);
	else
		msg = TTF_RenderUTF8_Solid(sdl->game_font, "YOU DIED", c);
	src = (SDL_Rect) {.x = W / 2 - msg->w / 2, .y = H / 2 - msg->h / 2 };
	i[2] = -1;
	while (++i[2] < 20)
		win_death_loop2(sdl, i, src, msg);
	SDL_FreeSurface(msg);
}

void		win_death(t_sdl *sdl, t_data *d, t_render *r)
{
	if (d->sectors[d->player.current_sector].end)
	{
		win_death_loop(sdl, 1);
		free_all_data(d, r);
		init(d, sdl);
		read_map(d, r);
		return ;
	}
	if (d->player.health <= 0)
	{
		win_death_loop(sdl, 0);
		free_all_data(d, r);
		init(d, sdl);
		read_map(d, r);
		return ;
	}
}
