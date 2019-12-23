/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawsector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkinzers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 19:13:45 by kkinzers          #+#    #+#             */
/*   Updated: 2019/08/12 19:13:47 by kkinzers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		intersect_peresech(t_ed *e, int wall, int i)
{
	e->in.x1 = e->dr.x1;
	e->in.y1 = e->dr.y1;
	e->in.x2 = e->dr.x2;
	e->in.y2 = e->dr.y2;
	e->in.x3 = e->s[i].w[wall].po_x1;
	e->in.y3 = e->s[i].w[wall].po_y1;
	e->in.x4 = e->s[i].w[wall].po_x2;
	e->in.y4 = e->s[i].w[wall].po_y2;
	return (intersection(e));
}

void	peresecheniye(t_ed *e, int i, int wall)
{
	e->per = 0;
	while (++i <= e->cur_sect - 1)
	{
		wall = 0;
		while (wall <= e->s[i].count_walls)
		{
			if ((e->dr.x1 == e->s[i].w[wall].po_x1 && e->dr.y1 ==
				e->s[i].w[wall].po_y1) || (e->dr.x1 == e->s[i].w[wall].po_x2
				&& e->dr.y1 == e->s[i].w[wall].po_y2))
			{
				wall++;
				continue ;
			}
			else
			{
				if (intersect_peresech(e, wall, i))
				{
					e->line_col = 0xFF0000;
					e->per = 1;
				}
			}
			wall++;
		}
	}
}

void	sup_build_line(t_ed *e)
{
	e->dr.x2 = e->mouse_x;
	e->dr.y2 = e->mouse_y;
	e->mouse_on = 1;
}

void	build_line(t_ed *e, int i, int x)
{
	e->per = 0;
	while (++i < DOTS_H * DOTS_W)
	{
		if (e->d[i].num_in_sect == x && e->d[i].active == 1)
		{
			x++;
			e->dr.x1 = e->d[i].pos_x;
			e->dr.y1 = e->d[i].pos_y;
			i = -1;
			while (++i < DOTS_H * DOTS_W)
				if (e->d[i].num_in_sect == x && e->d[i].active == 1)
				{
					e->dr.x2 = e->d[i].pos_x;
					e->dr.y2 = e->d[i].pos_y;
					i = -1;
					break ;
				}
			if (i != -1)
				sup_build_line(e);
		}
		line(e);
		e->mouse_on = 0;
		e->line_col = 0xFFFFFF;
	}
}

void	draw_sectors(t_ed *e, int c_sect, int c_wall)
{
	while (++c_sect < e->cur_sect)
	{
		c_wall = -1;
		while (++c_wall <= e->s[c_sect].count_walls)
		{
			e->dr.x1 = e->s[c_sect].w[c_wall].po_x1;
			e->dr.y1 = e->s[c_sect].w[c_wall].po_y1;
			e->dr.x2 = e->s[c_sect].w[c_wall].po_x2;
			e->dr.y2 = e->s[c_sect].w[c_wall].po_y2;
			if (e->s[c_sect].w[c_wall].sosed != -1)
				e->line_col = 0x00FFFF;
			if (e->s[c_sect].w[c_wall].transparent == 1)
				e->line_col = 0x59FFAC;
			if (e->s[c_sect].w[c_wall].doors != 0)
				e->line_col = 0x7D93FF;
			line(e);
			e->line_col = 0xFFFFFF;
		}
	}
}
