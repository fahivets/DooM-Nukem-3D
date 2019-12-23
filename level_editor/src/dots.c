/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dots.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkinzers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:28:29 by kkinzers          #+#    #+#             */
/*   Updated: 2019/09/09 19:28:30 by kkinzers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		intersect_check_cr_d(t_ed *e, int wall, int j)
{
	e->in.x1 = e->d[j].pos_x;
	e->in.y1 = e->d[j].pos_y;
	e->in.x2 = e->d[j].pos_x + 5000;
	e->in.y2 = e->d[j].pos_y + 100;
	e->in.x3 = e->s[e->cur_sect].w[wall].po_x1;
	e->in.y3 = e->s[e->cur_sect].w[wall].po_y1;
	e->in.x4 = e->s[e->cur_sect].w[wall].po_x2;
	e->in.y4 = e->s[e->cur_sect].w[wall].po_y2;
	return (intersection(e));
}

void	check_dot_cross(t_ed *e)
{
	int wall;
	int j;

	wall = 0;
	e->per = 0;
	j = -1;
	while (++j < DOTS_H * DOTS_W)
	{
		wall = 0;
		while (wall <= e->s[e->cur_sect].count_walls && e->d[j].cross != 5)
		{
			if (intersect_check_cr_d(e, wall, j))
				e->d[j].cross++;
			wall++;
		}
	}
}

void	clear_dots(t_ed *e, int i)
{
	e->number = -1;
	while (++i < DOTS_H * DOTS_W)
	{
		if (e->d[i].active == 1)
		{
			e->d[i].vertex = 1;
			e->d[i].active = 0;
		}
		if (e->d[i].num_in_sect < 9999)
			e->d[i].num_in_sect = 9999;
		if (e->d[i].vertex == 1 && e->d[i].to_sect < 9999)
			e->d[i].to_sect = 9999;
		if (e->d[i].cross > 0 && e->d[i].cross != 5)
		{
			if (e->d[i].cross == 1)
			{
				e->d[i].to_sect = e->cur_sect;
				e->d[i].cross = 5;
			}
			else
				e->d[i].cross = 0;
		}
	}
	e->cur_sect++;
}

void	write_dots(t_ed *e, int i, int yi, int xi)
{
	while (i < DOTS_H * DOTS_W)
	{
		xi = 0;
		e->p_x = 55;
		while (i < DOTS_H * DOTS_W && xi < DOTS_W)
		{
			e->d[i].x = xi * 3;
			e->d[i].y = yi * 3;
			e->d[i].pos_x = e->p_x;
			e->d[i].pos_y = e->p_y;
			e->d[i].active = 0;
			e->d[i].cross = 0;
			e->d[i].num_in_sect = 9999;
			e->d[i].to_sect = 9999;
			e->d[i].vertex = 0;
			e->d[i].vertex_n = -1;
			e->d[i].player = 0;
			e->d[i].end = 0;
			e->p_x += 15;
			xi++;
			i++;
		}
		yi++;
		e->p_y += 15;
	}
}
