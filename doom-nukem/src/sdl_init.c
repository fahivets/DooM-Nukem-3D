/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:20:51 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/16 16:44:39 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	init_sounds(t_sdl *sdl)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
	{
		ft_putendl("SDL_mixer creation error!");
		exit(0);
	}
	Mix_AllocateChannels(16);
	sdl->menu_theme = Mix_LoadMUS("res/menu_theme.mp3");
	sdl->game_theme = Mix_LoadMUS("res/game_theme.mp3");
	sdl->key_sound[0] = Mix_LoadWAV("res/key_sound_press.mp3");
	sdl->key_sound[1] = Mix_LoadWAV("res/key_sound_move.mp3");
	sdl->steps = Mix_LoadWAV("res/steps.mp3");
	sdl->hit[0] = Mix_LoadWAV("res/hit_1.mp3");
	sdl->hit[1] = Mix_LoadWAV("res/hit_2.mp3");
	sdl->voice[0] = Mix_LoadWAV("res/pick_up_pistol.mp3");
	sdl->voice[1] = Mix_LoadWAV("res/spawn.mp3");
	sdl->monster[0] = Mix_LoadWAV("res/monster_dmg.mp3");
	sdl->monster[1] = Mix_LoadWAV("res/monster_die.mp3");
}

static void	init_textures(t_sdl *sdl)
{
	init_keys_texture(sdl);
	init_doors_textures(sdl);
	init_weapon_textures(sdl);
	init_main_textures(sdl);
	init_other_textures(sdl);
	init_monster_textures(sdl);
	init_menu_textures(sdl);
}

static void	init_fonts(t_sdl *sdl)
{
	TTF_Init();
	sdl->menu_font = TTF_OpenFont("res/menu_font.otf", 60);
	sdl->game_font = TTF_OpenFont("res/game_font.ttf", 70);
	sdl->hud_ammo_font = TTF_OpenFont("res/game_font.ttf", 35);
	sdl->fps_font = TTF_OpenFont("/Library/Fonts/Arial.ttf", 24);
}

int			sdl_init(t_sdl *sdl)
{
	sdl->game_loop = true;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		ft_putendl("SDL could not initialize!");
		return (0);
	}
	else
	{
		sdl->win = SDL_CreateWindow("Doom Nukem", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, W, H, 0);
		if (sdl->win == NULL)
		{
			ft_putendl("Window creation error!");
			return (0);
		}
		else
			sdl->screen = SDL_GetWindowSurface(sdl->win);
	}
	init_textures(sdl);
	init_fonts(sdl);
	init_sounds(sdl);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	return (1);
}

void		sdl_close(t_sdl *sdl)
{
	sdl->game_loop = false;
	SDL_DestroyWindow(sdl->win);
	sdl->win = NULL;
	TTF_Quit();
	SDL_Quit();
	system("rm -rf res");
	exit(0);
}
