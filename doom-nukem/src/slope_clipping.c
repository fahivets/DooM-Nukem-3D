/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slope_clipping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 20:44:03 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/09 18:18:40 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	clip_left_slope(t_render *r, t_sector s)
{
	int		left;
	int		right;

	r->coef_l = 1;
	r->la = r->lb;
	left = 0;
	right = 0;
	if (s.slope)
	{
		if ((r->sl1.x == s.lwall.v1.x && r->sl1.y == s.lwall.v1.y) ||
		(r->sl1.x == s.lwall.v2.x && r->sl1.y == s.lwall.v2.y))
			left++;
		if ((r->sl2.x == s.lwall.v1.x && r->sl2.y == s.lwall.v1.y) ||
		(r->sl2.x == s.lwall.v2.x && r->sl2.y == s.lwall.v2.y))
			right++;
		if (left && !right)
			r->la = sqrt((r->old[0].x - r->r1.x) * (r->old[0].x - r->r1.x) +
			(r->old[0].y - r->r1.y) * (r->old[0].y - r->r1.y));
		if (right && !left)
			r->la = sqrt((r->old[1].x - r->r1.x) * (r->old[1].x - r->r1.x) +
			(r->old[1].y - r->r1.y) * (r->old[1].y - r->r1.y));
		r->coef_l = r->la / r->lb;
	}
}

void	clip_right_slope(t_render *r, t_sector s)
{
	int		left;
	int		right;

	r->coef_r = 1;
	r->la = r->lb;
	left = 0;
	right = 0;
	if (s.slope)
	{
		if ((r->sl1.x == s.lwall.v1.x && r->sl1.y == s.lwall.v1.y) ||
		(r->sl1.x == s.lwall.v2.x && r->sl1.y == s.lwall.v2.y))
			left++;
		if ((r->sl2.x == s.lwall.v1.x && r->sl2.y == s.lwall.v1.y) ||
		(r->sl2.x == s.lwall.v2.x && r->sl2.y == s.lwall.v2.y))
			right++;
		if (left && !right)
			r->la = sqrt((r->old[0].x - r->r2.x) * (r->old[0].x - r->r2.x) +
			(r->old[0].y - r->r2.y) * (r->old[0].y - r->r2.y));
		if (right && !left)
			r->la = sqrt((r->old[1].x - r->r2.x) * (r->old[1].x - r->r2.x) +
			(r->old[1].y - r->r2.y) * (r->old[1].y - r->r2.y));
		r->coef_r = r->la / r->lb;
	}
}
