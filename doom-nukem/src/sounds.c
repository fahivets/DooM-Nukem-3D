/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 17:01:12 by dsamarsk          #+#    #+#             */
/*   Updated: 2019/10/16 04:34:13 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	play_voice(t_sdl *sdl, t_data *d)
{
	if (d->player.weapon[1].have && d->player.weapon[1].pick_up)
	{
		play_game_sound(3, sdl->voice[0], 0, 100);
		d->player.weapon[1].pick_up = false;
	}
}

void		play_game_sound(int channel, Mix_Chunk *chunk_name,
							int loops, int volume)
{
	if (Mix_Playing(channel) == 0)
	{
		volume = volume > 128 ? (128) : (volume);
		Mix_Volume(channel, volume);
		Mix_PlayChannel(channel, chunk_name, loops);
	}
}

void		play_game_music(t_sdl *sdl)
{
	Mix_VolumeMusic(80);
	if (Mix_PlayingMusic() == 0)
		Mix_PlayMusic(sdl->game_theme, -1);
}

void		play_sounds(t_sdl *sdl, t_data *data)
{
	if (data->player.attacking)
	{
		if (data->player.aw == 1 && data->player.weapon[1].ammo > 0)
			play_game_sound(2, sdl->hit[1], 0, 100);
		if (data->player.aw == 0 && data->player.attacking == true)
			play_game_sound(1, sdl->hit[0], 0, 100);
	}
	play_voice(sdl, data);
}
