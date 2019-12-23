/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sector_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 19:16:36 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/16 14:48:45 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	init_sector_doors(t_data *d, int i)
{
	int j;

	j = -1;
	while (++j < d->sectors[i].wall_count)
	{
		d->sectors[i].all_doors[j].openned = false;
		d->sectors[i].all_doors[j].frame = 0;
		d->sectors[i].all_doors[j].keyid = d->sectors[i].doors[j];
		d->sectors[i].all_doors[j].full_open = false;
	}
}

static void	put_data_to_sector(char **arr, t_data *d, int i)
{
	int j;

	j = -1;
	while (++j < d->sectors[i].wall_count)
	{
		d->sectors[i].vertexes[j + 1] = d->all_vertexes[ft_atoi(arr[8 + j])];
		d->sectors[i].neighbors[j] = ft_atoi(arr[8 +
			d->sectors[i].wall_count + j]);
		d->sectors[i].textures[j] = ft_atoi(arr[8 +
			d->sectors[i].wall_count * 2 + j]);
		d->sectors[i].transparent[j] = ft_atoi(arr[8 +
			d->sectors[i].wall_count * 3 + j]);
		d->sectors[i].doors[j] = ft_atoi(arr[8 +
			d->sectors[i].wall_count * 4 + j]);
		if (d->sectors[i].doors[j] && d->sectors[i].neighbors[j] < 0)
			d->sectors[i].doors[j] = 0;
	}
	init_sector_doors(d, i);
	d->sectors[i].vertexes[0] = d->all_vertexes[ft_atoi(arr[7 + j])];
}

void		put_sector(char **arr, t_data *d)
{
	d->sectors[d->si].floor = ft_atoi(arr[1]);
	d->sectors[d->si].ceil = ft_atoi(arr[2]);
	d->sectors[d->si].skybox = ft_atoi(arr[3]);
	d->sectors[d->si].danger = ft_atoi(arr[4]);
	d->sectors[d->si].slope = ft_atoi(arr[5]);
	d->sectors[d->si].shade = ft_atoi(arr[6]);
	d->sectors[d->si].end = ft_atoi(arr[7]);
	if (d->sectors[d->si].danger)
		d->sectors[d->si].shade = 10;
	d->sectors[d->si].wall_count = (ft_array_len(arr) - 8) / 5;
	d->sectors[d->si].vertexes =
	(t_xy *)malloc(sizeof(t_xy) * (d->sectors[d->si].wall_count + 1));
	d->sectors[d->si].neighbors =
	(int *)malloc(sizeof(int) * d->sectors[d->si].wall_count);
	d->sectors[d->si].textures =
	(int *)malloc(sizeof(int) * d->sectors[d->si].wall_count);
	d->sectors[d->si].transparent =
	(char *)malloc(sizeof(char) * d->sectors[d->si].wall_count);
	d->sectors[d->si].doors =
	(char *)malloc(sizeof(char) * d->sectors[d->si].wall_count);
	d->sectors[d->si].all_doors =
	(t_door *)malloc(sizeof(t_door) * d->sectors[d->si].wall_count);
	put_data_to_sector(arr, d, d->si);
	d->si++;
}
