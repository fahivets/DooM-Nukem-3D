/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 16:07:21 by kkinzers          #+#    #+#             */
/*   Updated: 2019/10/16 20:50:14 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void			init(t_ed *e)
{
	e->i = 0;
	e->mouse_on = 0;
	e->number = -1;
	e->cur_sect = 0;
	e->per = 0;
	e->counter = 0;
	e->check_pl = 0;
	e->sosed_v1 = -1;
	e->sosed_v2 = -1;
	e->p_y = 50;
	e->key_door = 1;
	e->player.x = -1;
	e->player.y = -1;
	e->player.r = 0;
	e->player.sector = 0;
}

void			editor(t_ed *e)
{
	SDL_Window	*window;

	init(e);
	write_dots(e, 0, 0, 0);
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Level Editor", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, S_WI, S_HE, SDL_WINDOW_SHOWN);
	e->surface = SDL_GetWindowSurface(window);
	while (1)
	{
		SDL_FillRect(e->surface, NULL, 0x000000);
		SDL_GetMouseState(&e->mouse_x, &e->mouse_y);
		draw_map(e);
		events(e);
		SDL_UpdateWindowSurface(window);
	}
}

int				main(int argc, char **argv)
{
	t_ed		e;

	argv[1] = 0;
	if (argc > 0)
		editor(&e);
	return (0);
}
