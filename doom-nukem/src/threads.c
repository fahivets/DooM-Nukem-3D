/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 12:15:24 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/15 17:41:01 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	*cut_num(int num, int del)
{
	int		*arr;
	int		half;
	int		i;
	int		c;

	i = -1;
	arr = malloc(sizeof(int) * del);
	half = num / del;
	c = num % del;
	while (++i < del)
		arr[i] = half;
	while (c--)
		arr[--i] += 1;
	return (arr);
}

void		manage_treads(t_render *r, t_render *tmp, t_sdl *sdl, t_data *d)
{
	int *x;
	int j;
	int x2;

	j = -1;
	x = cut_num(r->endx - r->beginx, THREADS_C);
	x2 = r->beginx;
	while (++j < THREADS_C)
	{
		tmp[j].x = x2;
		tmp[j].endx = x2 + x[j];
		if (r->endx - r->beginx < THREADS_C)
		{
			tmp[j].x = r->beginx;
			tmp[j].endx = r->endx;
		}
		x2 += x[j];
		tmp[j].sdl = sdl;
		tmp[j].d = d;
		tmp[j].ii = r->i;
		tmp[j].s = r->ss;
	}
	free(x);
}

static void	calculate_nb_ceil_floor(t_render *r, t_data *d)
{
	r->nya = (r->x - r->s1.x) * (r->ny2a - r->ny1a) /
	(r->s3.x - r->s1.x) + r->ny1a;
	r->nyb = (r->x - r->s1.x) * (r->ny2b - r->ny1b) /
	(r->s3.x - r->s1.x) + r->ny1b;
	r->cnya = MAX(r->nya, d->topline[r->x]);
	r->cnya = MIN(r->cnya, d->bottomline[r->x]);
	r->cnyb = MAX(r->nyb, d->topline[r->x]);
	r->cnyb = MIN(r->cnyb, d->bottomline[r->x]);
	r->cnya = MIN(r->cnya, r->cyb);
}

void		*tread(void *param)
{
	t_render	*r;
	float		repeat[3];

	r = param;
	calculate_repeat(r, repeat);
	while (r->x <= r->endx)
	{
		calculate_texture_x(r, repeat);
		draw_floor_ceil(r, r->d, r->sdl);
		if (r->s.neighbors[r->ii] >= 0)
			calculate_nb_ceil_floor(r, r->d);
		if ((r->s.transparent[r->ii] && r->s.neighbors[r->ii] >= 0) ||
		r->s.doors[r->ii])
			draw_transparent_wall(r);
		if (r->s.neighbors[r->ii] >= 0)
			draw_divide_walls(r, r->d, r->sdl, r->s.neighbors[r->ii]);
		else
			draw_wall(r, r->sdl);
		r->x++;
	}
	pthread_exit(NULL);
}
