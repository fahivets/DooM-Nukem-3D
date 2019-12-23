/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cross.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkinzers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:41:05 by kkinzers          #+#    #+#             */
/*   Updated: 2019/10/16 16:41:06 by kkinzers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		intersect_conv(t_ed *e, t_conv *t)
{
	e->in.x1 = t->x1;
	e->in.y1 = t->y1;
	e->in.x2 = t->x2;
	e->in.y2 = t->y2;
	e->in.x3 = t->x3;
	e->in.y3 = t->y3;
	e->in.x4 = t->x4;
	e->in.y4 = t->y4;
	return (intersection(e));
}

void	init_t(t_ed *e, int j, t_conv *t)
{
	t->x1 = 0;
	t->y1 = 0;
	t->x2 = 0;
	t->y2 = 0;
	t->x3 = 0;
	t->y3 = 0;
	t->x4 = 0;
	t->y4 = 0;
	t->x1 = e->d[j].pos_x;
	t->y1 = e->d[j].pos_y;
}

void	find_x2y2(t_ed *e, t_conv *t, int i)
{
	while (++i < DOTS_H * DOTS_W)
		if (e->d[i].num_in_sect == e->number && t->x2 == 0 && t->y2 == 0)
		{
			t->x2 = e->d[i].pos_x;
			t->y2 = e->d[i].pos_y;
			break ;
		}
	t->num = -1;
}

void	work_check(t_ed *e, t_conv *t, int *j, int *i)
{
	if (t->num == e->d[*i].num_in_sect && t->x3 == 0 && t->y3 == 0)
	{
		t->x3 = e->d[*i].pos_x;
		t->y3 = e->d[*i].pos_y;
		t->num++;
		*i = 0;
	}
	if (t->num > 1 && *j == 0)
	{
		t->x3 = t->x4;
		t->y3 = t->y4;
		*j += 1;
	}
	if (t->num > 1 && t->num == e->d[*i].num_in_sect)
	{
		t->x4 = e->d[*i].pos_x;
		t->y4 = e->d[*i].pos_y;
	}
}

int		check_convex(t_ed *e, int j, int i)
{
	t_conv	t;

	init_t(e, j, &t);
	find_x2y2(e, &t, i);
	while (++t.num < e->number)
	{
		i = -1;
		j = 0;
		while (++i < DOTS_H * DOTS_W)
		{
			work_check(e, &t, &j, &i);
			if (t.num == e->d[i].num_in_sect && t.x4 == 0 && t.y4 == 0)
			{
				t.x4 = e->d[i].pos_x;
				t.y4 = e->d[i].pos_y;
				break ;
			}
		}
		if (intersect_conv(e, &t))
			return (0);
	}
	return (1);
}
