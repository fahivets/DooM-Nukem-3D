/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkinzers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 20:23:15 by kkinzers          #+#    #+#             */
/*   Updated: 2019/08/15 20:23:17 by kkinzers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		sdl_pixel_put(t_ed *e, int x, int y, int col)
{
	unsigned char	*pixel;

	pixel = e->surface->pixels;
	pixel[4 * (y * e->surface->w + x)] = col & 0xFF;
	pixel[4 * (y * e->surface->w + x) + 1] = (col >> 8) & 0xFF;
	pixel[4 * (y * e->surface->w + x) + 2] = (col >> 16) & 0xFF;
}

void		red_line(t_ed *e)
{
	sdl_pixel_put(e, round(e->dr.x1), round(e->dr.y1), e->line_col);
}

void		line(t_ed *e)
{
	e->dr.deltax = fabs(round(e->dr.x2) - round(e->dr.x1));
	e->dr.deltay = fabs(round(e->dr.y2) - round(e->dr.y1));
	e->dr.signx = round(e->dr.x1) < round(e->dr.x2) ? 1 : -1;
	e->dr.signy = round(e->dr.y1) < round(e->dr.y2) ? 1 : -1;
	e->dr.error = e->dr.deltax - e->dr.deltay;
	if (e->mouse_on == 1)
		peresecheniye(e, -1, 0);
	sdl_pixel_put(e, round(e->dr.x2), round(e->dr.y2), e->line_col);
	while (round(e->dr.x1) != round(e->dr.x2) ||
		round(e->dr.y1) != round(e->dr.y2))
	{
		red_line(e);
		e->dr.error2 = e->dr.error * 2;
		if (e->dr.error2 > -e->dr.deltay)
		{
			e->dr.error -= e->dr.deltay;
			e->dr.x1 += e->dr.signx;
		}
		if (e->dr.error2 < e->dr.deltax)
		{
			e->dr.error += e->dr.deltax;
			e->dr.y1 += e->dr.signy;
		}
	}
}

void		sup_green_circle(t_ed *e, int i, int x, int y)
{
	sdl_pixel_put(e, e->d[i].pos_x + x, e->d[i].pos_y - y, e->cir_col);
	sdl_pixel_put(e, e->d[i].pos_x + x, e->d[i].pos_y + y, e->cir_col);
	sdl_pixel_put(e, e->d[i].pos_x - x, e->d[i].pos_y - y, e->cir_col);
	sdl_pixel_put(e, e->d[i].pos_x - x, e->d[i].pos_y + y, e->cir_col);
	sdl_pixel_put(e, e->d[i].pos_x + y, e->d[i].pos_y - x, e->cir_col);
	sdl_pixel_put(e, e->d[i].pos_x + y, e->d[i].pos_y + x, e->cir_col);
	sdl_pixel_put(e, e->d[i].pos_x - y, e->d[i].pos_y - x, e->cir_col);
	sdl_pixel_put(e, e->d[i].pos_x - y, e->d[i].pos_y + x, e->cir_col);
}

void		draw_green_circle(t_ed *e, int i, int y, int radius)
{
	int		x;
	int		tx;
	int		ty;

	x = (radius - 1);
	tx = 1;
	ty = 1;
	e->error = (tx - (radius * 2));
	while (x >= y)
	{
		sup_green_circle(e, i, x, y);
		if (e->error <= 0)
		{
			++y;
			e->error += ty;
			ty += 2;
		}
		if (e->error > 0)
		{
			--x;
			tx += 2;
			e->error += (tx - (radius * 2));
		}
	}
}
