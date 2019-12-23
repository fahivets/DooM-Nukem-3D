/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 21:22:25 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/16 20:53:16 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	put_vertex(char **arr, t_data *d)
{
	d->all_vertexes[d->vi].x = ft_atoi(arr[1]);
	d->all_vertexes[d->vi].y = ft_atoi(arr[2]);
	d->vi++;
}

static void	put_sprite(char **arr, t_data *d)
{
	d->sprites[d->spi].position.x = ft_atoi(arr[1]);
	d->sprites[d->spi].position.y = ft_atoi(arr[2]);
	d->sprites[d->spi].startpos.x = d->sprites[d->spi].position.x;
	d->sprites[d->spi].startpos.y = d->sprites[d->spi].position.y;
	d->sprites[d->spi].sector = ft_atoi(arr[4]);
	d->sprites[d->spi].position.z = d->sectors[d->sprites[d->spi].sector].floor
	+ ft_atoi(arr[3]);
	d->sprites[d->spi].h = ft_atoi(arr[5]);
	d->sprites[d->spi].w = ft_atoi(arr[6]);
	d->sprites[d->spi].type = ft_atoi(arr[7]);
	d->sprites[d->spi].id = ft_atoi(arr[8]);
	if (d->sprites[d->spi].id == 0)
		d->sprites[d->spi].damage = 13;
	d->sprites[d->spi].animated = ft_atoi(arr[9]);
	d->sprites[d->spi].attack = 0;
	d->sprites[d->spi].alive = 1;
	d->sprites[d->spi].active = 0;
	d->sprites[d->spi].health = 100;
	d->sprites[d->spi].frame = 0;
	d->sprites[d->spi].damaged = 0;
	d->sprites[d->spi].rendered = 0;
	d->spi++;
}

static void	put_player(char **arr, t_data *d)
{
	d->player.position.x = ft_atoi(arr[1]);
	d->player.position.y = ft_atoi(arr[2]);
	d->player.angle = ft_atoi(arr[3]);
	d->player.current_sector = ft_atoi(arr[4]);
}

static void	put_map_data(t_data *d)
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
			put_vertex(arr, d);
		if (arr[0] && !ft_strcmp(arr[0], "sector"))
			put_sector(arr, d);
		if (arr[0] && !ft_strcmp(arr[0], "sprite"))
			put_sprite(arr, d);
		if (arr[0] && !ft_strcmp(arr[0], "player"))
			put_player(arr, d);
		free(line);
		free_array(arr);
	}
	free(line);
}

void		read_map(t_data *d, t_render *r)
{
	int j;

	j = -1;
	calculate_map_data(d);
	put_map_data(d);
	validate_map(d);
	d->player.height = PLAYERZ;
	d->player.position.z = d->sectors[d->player.current_sector].floor
	+ d->player.height;
	d->player.vertical_angle = 0;
	r->left_x = (int *)malloc(sizeof(int) * d->sector_count);
	r->right_x = (int *)malloc(sizeof(int) * d->sector_count);
	d->rendered_sectors = (int *)malloc(sizeof(int) * d->sector_count);
	d->topline_n = (int **)malloc(sizeof(int*) * d->sector_count);
	d->bottomline_n = (int **)malloc(sizeof(int*) * d->sector_count);
	d->left_x = (int **)malloc(sizeof(int*) * d->sector_count);
	while (++j < d->sector_count)
	{
		d->topline_n[j] = (int *)malloc(sizeof(int) * W);
		d->bottomline_n[j] = (int *)malloc(sizeof(int) * W);
		d->left_x[j] = (int *)malloc(sizeof(int) * W);
	}
	manage_slope_sectors(d);
	add_sprites_to_sector(d);
}
