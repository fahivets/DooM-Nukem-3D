/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkinzers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 18:07:49 by kkinzers          #+#    #+#             */
/*   Updated: 2019/07/31 18:07:50 by kkinzers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		draw_lines(t_ed *e)
{
	e->dr.x1 = START_LINE;
	e->dr.y1 = START_LINE;
	e->dr.x2 = S_WI - END_LINE;
	e->dr.y2 = START_LINE;
	line(e);
	e->dr.x1 = e->dr.x2;
	e->dr.y1 = e->dr.y2;
	e->dr.y2 = S_HE - 25;
	line(e);
	e->dr.x1 = e->dr.x2;
	e->dr.y1 = e->dr.y2;
	e->dr.x2 = START_LINE;
	line(e);
	e->dr.x1 = e->dr.x2;
	e->dr.y1 = e->dr.y2;
	e->dr.y2 = START_LINE;
	line(e);
}

void		check_mouse_position(t_ed *e, int i, int x, int y)
{
	e->cir_col = 0xFFFF00;
	while (++y <= 6)
	{
		x = -7;
		while (++x <= 6)
			if (e->mouse_x + x == e->d[i].pos_x)
				if (e->mouse_y + y == e->d[i].pos_y)
				{
					e->cir_col = 0x00FF00;
					break ;
				}
	}
	if (e->d[i].vertex == 1)
		e->cir_col = 0x00FFFF;
	if (e->d[i].active == 1)
		e->cir_col = 0x00FF00;
	if (e->d[i].player == 1)
		e->cir_col = 0xFF00FF;
	if (e->d[i].end == 1)
		e->cir_col = 0xA30018;
}

void		draw_map(t_ed *e)
{
	int	i;

	draw_lines(e);
	i = -1;
	e->line_col = 0xFFFFFF;
	while (++i < DOTS_H * DOTS_W)
	{
		check_mouse_position(e, i, -7, -7);
		sdl_pixel_put(e, e->d[i].pos_x, e->d[i].pos_y, 0xFFFFFF);
		draw_green_circle(e, i, 0, 2);
	}
	build_line(e, -1, 0);
	if (e->cur_sect > 0)
		draw_sectors(e, -1, -1);
}
