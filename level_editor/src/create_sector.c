/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkinzers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 18:28:42 by kkinzers          #+#    #+#             */
/*   Updated: 2019/09/20 18:28:43 by kkinzers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	sup_write_sector(t_ed *e, int l_number, int wall, int i)
{
	while (++i < DOTS_H * DOTS_W)
		if (e->d[i].num_in_sect == l_number)
		{
			e->s[e->cur_sect].w[wall].v2 = e->d[i].vertex_n;
			e->s[e->cur_sect].w[wall].po_x2 = e->d[i].pos_x;
			e->s[e->cur_sect].w[wall].po_y2 = e->d[i].pos_y;
			break ;
		}
}

void	sttd(t_ed *e, int wall)
{
	e->s[e->cur_sect].w[wall].sosed = -1;
	e->s[e->cur_sect].w[wall].textures = 0;
	e->s[e->cur_sect].w[wall].transparent = 0;
	e->s[e->cur_sect].w[wall].doors = 0;
}

void	write_sector(t_ed *e, int i, int l_number, int wall)
{
	e->s[e->cur_sect].count_walls = e->number;
	e->s[e->cur_sect].w = (t_wall *)malloc(sizeof(t_wall) * (e->number + 1));
	floor_ceil_skybox(e);
	while (++i < DOTS_H * DOTS_W)
		if (e->d[i].num_in_sect == l_number)
		{
			e->s[e->cur_sect].w[wall].v1 = e->d[i].vertex_n;
			e->s[e->cur_sect].w[wall].po_x1 = e->d[i].pos_x;
			e->s[e->cur_sect].w[wall].po_y1 = e->d[i].pos_y;
			sttd(e, wall);
			if (wall == e->s[e->cur_sect].count_walls)
			{
				e->s[e->cur_sect].w[wall].v2 = e->s[e->cur_sect].w[0].v1;
				e->s[e->cur_sect].w[wall].po_x2 = e->s[e->cur_sect].w[0].po_x1;
				e->s[e->cur_sect].w[wall].po_y2 = e->s[e->cur_sect].w[0].po_y1;
				break ;
			}
			else
				l_number++;
			sup_write_sector(e, l_number, wall, -1);
			i = -1;
			wall++;
		}
	check_dot_cross(e);
}

int		sup_fill_sector(t_ed *e, int i)
{
	if (e->d[i].vertex != 1 && !check_one_pix(e, i))
		return (0);
	if (e->number > 1)
		if (!check_convex(e, i, -1))
			return (0);
	e->number++;
	e->d[i].num_in_sect = e->number;
	e->d[i].active = 1;
	e->d[i].to_sect = e->cur_sect;
	if (e->d[i].vertex_n == -1)
	{
		e->d[i].vertex_n = e->counter;
		e->counter++;
	}
	return (1);
}

int		fill_sector(t_ed *e, int i)
{
	if (e->d[i].active == 0 && e->d[i].cross != 5 && e->per != 1)
	{
		if (!sup_fill_sector(e, i))
			return (0);
	}
	else if (e->d[i].active == 1 && e->d[i].num_in_sect == 0 && e->number > 2)
	{
		clockwise(e);
		write_sector(e, -1, 0, 0);
		clear_dots(e, -1);
	}
	else if ((e->d[i].active == 1 && e->d[i].num_in_sect > 0 &&
		e->d[i].num_in_sect < e->number) || e->d[i].cross == 5 || e->per == 1 ||
		(e->d[i].num_in_sect == 0 && e->number < 3 && e->number > 0))
		return (0);
	else
	{
		e->number--;
		e->d[i].active = 0;
		e->d[i].num_in_sect = 9999;
		if (e->d[i].vertex_n == e->counter)
			e->d[i].vertex_n = -1;
		e->counter--;
	}
	return (1);
}
