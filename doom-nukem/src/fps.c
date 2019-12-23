/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:53:53 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/11 20:09:14 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	show_fps(t_data *d, t_sdl *sdl)
{
	SDL_Rect	srcrect;
	SDL_Color	color;
	SDL_Surface	*message;
	char		*str;

	if (!sdl->show_fps)
		return ;
	color.r = 0;
	color.g = 255;
	color.b = 0;
	str = ft_itoa(d->fps);
	message = TTF_RenderText_Solid(sdl->fps_font, str, color);
	srcrect.x = W - message->w;
	srcrect.y = 0;
	SDL_BlitSurface(message, NULL, sdl->screen, &srcrect);
	SDL_FreeSurface(message);
	free(str);
	if (d->current_time > d->time_fps + 1000)
	{
		d->fps = d->frame;
		d->frame = 0;
		d->time_fps = d->current_time;
	}
	d->frame++;
}
