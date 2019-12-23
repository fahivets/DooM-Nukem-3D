/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_sounds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 03:18:42 by dsamarsk          #+#    #+#             */
/*   Updated: 2019/10/16 04:26:11 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		play_key_sound(int channel, Mix_Chunk *chunk_name,
							int loops, int volume)
{
	channel = Mix_PlayChannel(channel, chunk_name, loops);
	if (channel < 0)
		return ;
	if (Mix_Playing(channel) != 0)
	{
		volume = volume > 128 ? (128) : (volume);
		Mix_Volume(channel, volume);
		Mix_PlayChannel(channel, chunk_name, loops);
	}
}

static void	play_menu_music(t_sdl *sdl)
{
	Mix_VolumeMusic(100);
	if (Mix_PlayingMusic() == 0)
		Mix_PlayMusic(sdl->menu_theme, 0);
}

void		play_menu_sounds(t_sdl *sdl)
{
	if (sdl->menu_loop | sdl->options_loop | sdl->difficulty_loop)
		play_menu_music(sdl);
	else
		Mix_HaltMusic();
}
