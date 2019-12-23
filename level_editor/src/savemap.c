/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   savemap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 19:41:02 by kkinzers          #+#    #+#             */
/*   Updated: 2019/10/16 21:56:06 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	write_vert_to_map(t_ed *e, int fd)
{
	int	i;
	int	vert;

	i = -1;
	vert = 0;
	while (++i < DOTS_H * DOTS_W)
	{
		if (vert == e->d[i].vertex_n)
		{
			ft_putendl_fd("vertex ", fd);
			ft_putendl_fd(ft_itoa(e->d[i].x), fd);
			ft_putendl_fd(" ", fd);
			ft_putendl_fd(ft_itoa(e->d[i].y), fd);
			ft_putendl_fd("\n", fd);
			vert++;
			i = -1;
		}
	}
}

void	write_player_sprites(t_ed *e, int fd)
{
	ft_putendl_fd("player", fd);
	ft_putendl_fd(" ", fd);
	ft_putendl_fd(ft_itoa(e->player.x), fd);
	ft_putendl_fd(" ", fd);
	ft_putendl_fd(ft_itoa(e->player.y), fd);
	ft_putendl_fd(" ", fd);
	ft_putendl_fd(ft_itoa(e->player.r), fd);
	ft_putendl_fd(" ", fd);
	ft_putendl_fd(ft_itoa(e->player.sector), fd);
}

void	save_map(t_ed *e)
{
	int	fd;

	e->i = 0;
	system("rm -rf assets/map.txt");
	fd = open("assets/map.txt", O_RDWR | O_CREAT, S_IREAD | S_IWRITE);
	write_vert_to_map(e, fd);
	write_sect_to_map(e, fd, 0);
	write_player_sprites(e, fd);
	pack();
}
