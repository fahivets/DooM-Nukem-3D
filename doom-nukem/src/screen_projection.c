/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_projection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 20:57:53 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/10 00:03:42 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	calc_screen_coord(t_render *r, t_data *d, t_sector s)
{
	calc_screen_slope(r, s);
	r->s1z = r->ceil + r->ceil1 * r->coef_l;
	r->s2z = r->floor + r->floor1 * r->coef_l;
	r->s3z = r->ceil + r->ceil2 * r->coef_r;
	r->s4z = r->floor + r->floor2 * r->coef_r;
	r->s1.x = (W / 2) - (int)(r->xscale1 * r->r1.x);
	r->s1.y = (H / 2) - (int)(r->yscale1 *
	(r->s1z + r->r1.y * d->player.vertical_angle));
	r->s2.x = (W / 2) - (int)(r->xscale1 * r->r1.x);
	r->s2.y = (H / 2) - (int)(r->yscale1 *
	(r->s2z + r->r1.y * d->player.vertical_angle));
	r->s3.x = (W / 2) - (int)(r->xscale2 * r->r2.x);
	r->s3.y = (H / 2) - (int)(r->yscale2 *
	(r->s3z + r->r2.y * d->player.vertical_angle));
	r->s4.x = (W / 2) - (int)(r->xscale2 * r->r2.x);
	r->s4.y = (H / 2) - (int)(r->yscale2 *
	(r->s4z + r->r2.y * d->player.vertical_angle));
}

static void	calc_nb_screen_coord(t_render *r, t_data *d, t_sector s)
{
	calc_nb_slope(r, d, s);
	r->nbceil = d->sectors[s.neighbors[r->i]].ceil - d->player.position.z;
	r->nbfloor = d->sectors[s.neighbors[r->i]].floor - d->player.position.z;
	r->ny1a = (H / 2) + (int)(r->yscale1 *
	-(r->nbceil + r->ceil1 * r->coef_l + r->r1.y * d->player.vertical_angle));
	r->ny1b = (H / 2) + (int)(r->yscale1 *
	-(r->nbfloor + r->floor1 * r->coef_l + r->r1.y * d->player.vertical_angle));
	r->ny2a = (H / 2) + (int)(r->yscale2 *
	-(r->nbceil + r->ceil2 * r->coef_r + r->r2.y * d->player.vertical_angle));
	r->ny2b = (H / 2) + (int)(r->yscale2 *
	-(r->nbfloor + r->floor2 * r->coef_r + r->r2.y * d->player.vertical_angle));
}

void		screen_proj(t_render *r, t_data *d, t_sector s)
{
	r->xscale1 = HFOV / r->r1.y;
	r->xscale2 = HFOV / r->r2.y;
	r->yscale1 = VFOV / r->r1.y;
	r->yscale2 = VFOV / r->r2.y;
	r->nbceil = 0;
	r->nbfloor = 0;
	r->ceil = s.ceil - d->player.position.z;
	r->floor = s.floor - d->player.position.z;
	calc_screen_coord(r, d, s);
	if (s.neighbors[r->i] >= 0)
		calc_nb_screen_coord(r, d, s);
}

void		screen_proj_sprite(t_render *r, t_data *d, int i)
{
	r->xscale1 = HFOV / r->r1.y;
	r->xscale2 = HFOV / r->r2.y;
	r->yscale1 = VFOV / r->r1.y;
	r->yscale2 = VFOV / r->r2.y;
	r->ceil = d->sprites[i].position.z + d->sprites[i].h - d->player.position.z;
	r->floor = d->sprites[i].position.z - d->player.position.z;
	r->s1.x = (W / 2) - (int)(r->xscale1 * r->r1.x);
	r->s1.y = (H / 2) + (int)(r->yscale1 *
	-(r->ceil + r->r1.y * d->player.vertical_angle));
	r->s2.x = r->s1.x;
	r->s2.y = (H / 2) + (int)(r->yscale1 *
	-(r->floor + r->r1.y * d->player.vertical_angle));
	r->s3.x = (W / 2) - (int)(r->xscale2 * r->r2.x);
	r->s3.y = (H / 2) + (int)(r->yscale2 *
	-(r->ceil + r->r2.y * d->player.vertical_angle));
	r->s4.x = r->s3.x;
	r->s4.y = (H / 2) + (int)(r->yscale2 *
	-(r->floor + r->r2.y * d->player.vertical_angle));
}
