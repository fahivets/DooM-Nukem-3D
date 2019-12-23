/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 21:24:41 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/17 15:10:49 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	mouse_hook(t_data *d)
{
	int x;
	int y;

	SDL_GetRelativeMouseState(&x, &y);
	d->player.angle += x * 0.005;
	if (d->player.angle >= M_PI * 2)
		d->player.angle -= M_PI * 2;
	if (d->player.angle <= 0)
		d->player.angle += M_PI * 2;
	d->player.vertical_angle += y * 0.02;
	if (d->player.vertical_angle <= -4)
		d->player.vertical_angle = -4;
	if (d->player.vertical_angle >= 4)
		d->player.vertical_angle = 4;
	d->player.anglesin = sinf(d->player.angle);
	d->player.anglecos = cosf(d->player.angle);
}
