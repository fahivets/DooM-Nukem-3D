/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slopes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 22:09:21 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/13 17:07:45 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static t_wall	get_lwall(t_sector *s, t_data *data)
{
	int		i;
	t_wall	low;

	i = -1;
	while (++i < s->wall_count)
	{
		if (s->neighbors[i] >= 0)
		{
			if (data->sectors[s->neighbors[i]].floor == s->slope_nb[0].floor)
			{
				low.v1.x = s->vertexes[i].x;
				low.v1.y = s->vertexes[i].y;
				low.v2.x = s->vertexes[i + 1].x;
				low.v2.y = s->vertexes[i + 1].y;
			}
		}
	}
	return (low);
}

static t_wall	get_hwall(t_sector *s, t_data *data)
{
	int		i;
	t_wall	high;

	i = -1;
	while (++i < s->wall_count)
	{
		if (s->neighbors[i] >= 0)
		{
			if (data->sectors[s->neighbors[i]].floor == s->slope_nb[1].floor)
			{
				high.v1.x = s->vertexes[i].x;
				high.v1.y = s->vertexes[i].y;
				high.v2.x = s->vertexes[i + 1].x;
				high.v2.y = s->vertexes[i + 1].y;
			}
		}
	}
	return (high);
}

static t_sector	*get_slope_nb(t_sector *s, t_data *data)
{
	t_sector	*nb;
	t_sector	tmp;
	int			i;
	int			count;

	nb = (t_sector *)malloc(sizeof(t_sector) * 2);
	count = 0;
	i = -1;
	while (++i < s->wall_count)
	{
		if (s->neighbors[i] >= 0)
		{
			nb[count] = data->sectors[s->neighbors[i]];
			count++;
		}
	}
	if (nb[0].floor > nb[1].floor)
	{
		tmp = nb[0];
		nb[0] = nb[1];
		nb[1] = tmp;
	}
	return (nb);
}

void			manage_slope_sectors(t_data *d)
{
	int			i;
	t_sector	*s;

	i = -1;
	while (++i < d->sector_count)
	{
		s = &d->sectors[i];
		if (s->slope)
		{
			s->slope_nb = get_slope_nb(s, d);
			s->floor = s->slope_nb[0].floor;
			s->ceil = s->slope_nb[0].ceil;
			s->floor_slope = s->slope_nb[1].floor - s->slope_nb[0].floor;
			s->ceil_slope = s->slope_nb[1].ceil - s->slope_nb[0].ceil;
			if (s->floor_slope == 0 && s->ceil_slope == 0)
			{
				s->slope = 0;
				return ;
			}
			s->lwall = get_lwall(s, d);
			s->hwall = get_hwall(s, d);
		}
	}
}
