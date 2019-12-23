/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slopes2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 20:23:11 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/10 00:03:29 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	calc_screen_slope2(t_render *r, t_sector s)
{
	if ((r->sl1.x == s.hwall.v1.x && r->sl1.y == s.hwall.v1.y) ||
	(r->sl1.x == s.hwall.v2.x && r->sl1.y == s.hwall.v2.y))
	{
		r->floor1 = s.floor_slope;
		r->ceil1 = s.ceil_slope;
	}
	if (((r->sl1.x == s.lwall.v1.x && r->sl1.y == s.lwall.v1.y) ||
	(r->sl1.x == s.lwall.v2.x && r->sl1.y == s.lwall.v2.y)) && r->coef_l != 1)
	{
		r->floor1 = s.floor_slope;
		r->ceil1 = s.ceil_slope;
	}
	if ((r->sl2.x == s.hwall.v1.x && r->sl2.y == s.hwall.v1.y) ||
	(r->sl2.x == s.hwall.v2.x && r->sl2.y == s.hwall.v2.y))
	{
		r->floor2 = s.floor_slope;
		r->ceil2 = s.ceil_slope;
	}
	if (((r->sl2.x == s.lwall.v1.x && r->sl2.y == s.lwall.v1.y) ||
	(r->sl2.x == s.lwall.v2.x && r->sl2.y == s.lwall.v2.y)) && r->coef_r != 1)
	{
		r->floor2 = s.floor_slope;
		r->ceil2 = s.ceil_slope;
	}
}

void		calc_screen_slope(t_render *r, t_sector s)
{
	r->floor1 = 0;
	r->ceil1 = 0;
	r->floor2 = 0;
	r->ceil2 = 0;
	if (s.slope)
		calc_screen_slope2(r, s);
}

static void	calc_nb_screen_slope3(t_render *r, t_sector nb)
{
	if ((r->sl2.x == nb.hwall.v1.x && r->sl2.y == nb.hwall.v1.y) ||
	(r->sl2.x == nb.hwall.v2.x && r->sl2.y == nb.hwall.v2.y))
	{
		r->floor2 = nb.floor_slope;
		r->ceil2 = nb.ceil_slope;
	}
	if (((r->sl2.x == nb.lwall.v1.x && r->sl2.y == nb.lwall.v1.y) ||
	(r->sl2.x == nb.lwall.v2.x && r->sl2.y == nb.lwall.v2.y)) && r->coef_r != 1)
	{
		r->floor2 = nb.floor_slope;
		r->ceil2 = nb.ceil_slope;
	}
}

static void	calc_nb_screen_slope2(t_render *r, t_data *d, t_sector s)
{
	t_sector nb;

	nb = d->sectors[s.neighbors[r->i]];
	if ((r->sl1.x == nb.hwall.v1.x && r->sl1.y == nb.hwall.v1.y) ||
	(r->sl1.x == nb.hwall.v2.x && r->sl1.y == nb.hwall.v2.y))
	{
		r->floor1 = nb.floor_slope;
		r->ceil1 = nb.ceil_slope;
	}
	if (((r->sl1.x == nb.lwall.v1.x && r->sl1.y == nb.lwall.v1.y) ||
	(r->sl1.x == nb.lwall.v2.x && r->sl1.y == nb.lwall.v2.y)) && r->coef_l != 1)
	{
		r->floor1 = nb.floor_slope;
		r->ceil1 = nb.ceil_slope;
	}
	calc_nb_screen_slope3(r, nb);
}

void		calc_nb_slope(t_render *r, t_data *d, t_sector s)
{
	r->floor1 = 0;
	r->ceil1 = 0;
	r->floor2 = 0;
	r->ceil2 = 0;
	if (d->sectors[s.neighbors[r->i]].slope)
		calc_nb_screen_slope2(r, d, s);
}
