/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sup_create_sector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 00:38:51 by kkinzers          #+#    #+#             */
/*   Updated: 2019/10/17 14:55:28 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	floor_ceil_skybox(t_ed *e)
{
	e->s[e->cur_sect].skybox = 0;
	e->s[e->cur_sect].floor = 0;
	e->s[e->cur_sect].ceil = 20;
	e->s[e->cur_sect].naklon = 0;
	e->s[e->cur_sect].danger = 0;
	e->s[e->cur_sect].light = 8;
	e->s[e->cur_sect].end = 0;
}

int		intersect_check_one_pix(t_ed *e, int wall, int j, int i)
{
	e->in.x1 = e->d[j].pos_x;
	e->in.y1 = e->d[j].pos_y;
	e->in.x2 = e->d[j].pos_x - 1;
	e->in.y2 = e->d[j].pos_y - 1;
	e->in.x3 = e->s[i].w[wall].po_x1;
	e->in.y3 = e->s[i].w[wall].po_y1;
	e->in.x4 = e->s[i].w[wall].po_x2;
	e->in.y4 = e->s[i].w[wall].po_y2;
	return (intersection(e));
}

int		check_one_pix(t_ed *e, int j)
{
	int	i;
	int	wall;

	i = -1;
	wall = 0;
	e->per = 0;
	while (++i <= e->cur_sect - 1)
	{
		wall = 0;
		while (wall <= e->s[i].count_walls)
		{
			if (intersect_check_one_pix(e, wall, j, i))
				return (0);
			wall++;
		}
	}
	return (1);
}
