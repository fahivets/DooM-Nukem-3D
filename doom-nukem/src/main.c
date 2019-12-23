/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:19:46 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/17 13:43:53 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	draw_lava_damage_taking(t_sdl *sdl, t_data *d)
{
	SDL_Rect left;
	SDL_Rect right;

	if (d->player.taking_lava_damage)
	{
		left.x = 0;
		left.y = H / 2 - sdl->fire_left->h / 2;
		right.x = W - sdl->fire_right->w;
		right.y = H / 2 - sdl->fire_right->h / 2;
		SDL_BlitSurface(sdl->fire_left, NULL, sdl->screen, &left);
		SDL_BlitSurface(sdl->fire_right, NULL, sdl->screen, &right);
	}
}

static void	game_cycle(t_sdl *sdl, t_data *d, t_render *r)
{
	win_death(sdl, d, r);
	menu(sdl, d);
	draw_skybox(sdl, d);
	init_repeat(d, r);
	timers(d, sdl);
	draw_screen(sdl, r, d, d->player.current_sector);
	draw_all_sprites(sdl, d);
	move_sprites(d);
	key_hooks(sdl, d);
	mouse_hook(d);
	move(sdl, d);
	show_fps(d, sdl);
	draw_weapon(sdl, d);
	draw_hud(sdl, d);
	draw_lava_damage_taking(sdl, d);
	SDL_Delay(10);
	SDL_UpdateWindowSurface(sdl->win);
	play_game_music(sdl);
	play_sounds(sdl, d);
}

int			main(int argc, char **argv)
{
	t_sdl		sdl;
	t_data		data;
	t_render	render;

	if (argc != 2 || !validate(argv[1]))
		usage();
	unpack(argv[1]);
	sdl.language = false;
	init(&data, &sdl);
	read_map(&data, &render);
	if (!sdl_init(&sdl))
	{
		ft_putendl("SDL could not initialize!");
		return (0);
	}
	while (sdl.game_loop)
		game_cycle(&sdl, &data, &render);
}
