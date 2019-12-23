/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_map_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 20:10:40 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/16 15:20:20 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	calculate_map_data(t_data *d)
{
	int		fd;
	char	*line;
	char	**arr;

	fd = open("res/map.txt", O_RDONLY);
	if (fd <= 0 || read(fd, NULL, 0) < 0)
		usage();
	while (get_next_line(fd, &line))
	{
		ft_tabs_to_spaces(line);
		arr = ft_strsplit(line, ' ');
		if (arr[0] && !ft_strcmp(arr[0], "vertex"))
			d->vertex_count++;
		if (arr[0] && !ft_strcmp(arr[0], "sector"))
			d->sector_count++;
		if (arr[0] && !ft_strcmp(arr[0], "sprite"))
			d->sprite_count++;
		free(line);
		free_array(arr);
	}
	free(line);
	d->all_vertexes = (t_xy *)malloc(sizeof(t_xy) * d->vertex_count);
	d->sectors = (t_sector *)malloc(sizeof(t_sector) * d->sector_count);
	d->sprites = (t_sprite *)malloc(sizeof(t_sprite) * d->sprite_count);
}
