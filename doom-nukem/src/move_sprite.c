/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 20:58:01 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/15 17:15:50 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	calc_sprite_move_vector(t_data *d, int i)
{
	float v[2];
	float vec_len;

	v[0] = (d->sprites[i].position.x - d->player.position.x);
	v[1] = (d->sprites[i].position.y - d->player.position.y);
	vec_len = sqrt(v[0] * v[0] + v[1] * v[1]);
	v[0] /= vec_len;
	v[1] /= vec_len;
	d->sprite_dx = v[0] * 0.1;
	d->sprite_dy = v[1] * 0.1;
}

static void	calc_sprite_move_vector_back(t_data *d, int i)
{
	float v[2];
	float vec_len;

	v[0] = (d->sprites[i].position.x - d->sprites[i].startpos.x);
	v[1] = (d->sprites[i].position.y - d->sprites[i].startpos.y);
	vec_len = sqrt(v[0] * v[0] + v[1] * v[1]);
	v[0] /= vec_len;
	v[1] /= vec_len;
	d->sprite_dx = v[0] * 0.1;
	d->sprite_dy = v[1] * 0.1;
}

static void	move_sprite_back(t_data *d, int i)
{
	if (d->sprites[i].dtp > 20 && d->sprites[i].type == 1 &&
	d->sprites[i].alive && d->sprites[i].active && fabs(d->sprites[i].position.x
	- d->sprites[i].startpos.x) > 1 && fabs(d->sprites[i].position.y -
	d->sprites[i].startpos.y) > 1)
	{
		calc_sprite_move_vector_back(d, i);
		if (d->sprites[i].dtp > 2 && d->sprites[i].frame > 13)
		{
			collision_sprite(d, i);
			d->sprites[i].position.x -= d->sprite_dx;
			d->sprites[i].position.y -= d->sprite_dy;
			update_sprite_sector(d, i);
		}
	}
}

void		move_sprites(t_data *d)
{
	int		i;

	i = -1;
	d->sprite_dx = 0;
	d->sprite_dy = 0;
	while (++i < d->sprite_count)
	{
		if (d->sprites[i].sector == d->player.current_sector)
			d->sprites[i].active = 1;
		if (d->sprites[i].dtp < 20 && d->sprites[i].type == 1 &&
		d->sprites[i].alive && d->sprites[i].active)
		{
			calc_sprite_move_vector(d, i);
			if (d->sprites[i].dtp > 2 && d->sprites[i].frame < 4)
			{
				collision_sprite(d, i);
				d->sprites[i].position.x -= d->sprite_dx;
				d->sprites[i].position.y -= d->sprite_dy;
				update_sprite_sector(d, i);
			}
		}
		move_sprite_back(d, i);
	}
}
