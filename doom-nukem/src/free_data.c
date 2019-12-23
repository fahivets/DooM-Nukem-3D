/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 03:35:41 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/16 03:37:20 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	free_all_data2(t_data *d)
{
	int i;

	i = -1;
	while (++i < d->sector_count)
	{
		free(d->topline_n[i]);
		free(d->bottomline_n[i]);
		free(d->left_x[i]);
		free(d->sectors[i].vertexes);
		free(d->sectors[i].neighbors);
		free(d->sectors[i].textures);
		free(d->sectors[i].transparent);
		free(d->sectors[i].doors);
		free(d->sectors[i].all_doors);
		if (d->sectors[i].sprite_count > 0)
			free(d->sectors[i].sprites);
		if (d->sectors[i].slope)
			free(d->sectors[i].slope_nb);
	}
	free(d->left_x);
	free(d->topline_n);
	free(d->bottomline_n);
	free(d->all_vertexes);
	free(d->sprites);
	free(d->sectors);
}

void		free_all_data(t_data *d, t_render *r)
{
	int i;

	i = -1;
	while (++i < H)
		free(d->transparent_mask[i]);
	free(d->transparent_mask);
	free(d->topline);
	free(d->bottomline);
	free(r->left_x);
	free(r->right_x);
	free(d->rendered_sectors);
	free_all_data2(d);
}

void		free_array(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
