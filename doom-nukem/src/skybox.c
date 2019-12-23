/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:25:47 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/15 15:26:05 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	draw_skybox(t_sdl *sdl, t_data *d)
{
	SDL_Rect srcrect;

	srcrect.x = (sdl->skybox->w - W) - (int)((sdl->skybox->w - W) * (6.28319
	- d->player.angle) / 6.28319) % (sdl->skybox->w - W);
	srcrect.y = (sdl->skybox->h - H) - (int)((sdl->skybox->h - H) * ((10
	- d->player.vertical_angle + 5) / 10)) % (sdl->skybox->h - H);
	srcrect.w = W;
	srcrect.h = H;
	SDL_BlitSurface(sdl->skybox, &srcrect, sdl->screen, NULL);
}
