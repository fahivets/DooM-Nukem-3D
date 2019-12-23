/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   savemap1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkinzers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 04:14:01 by kkinzers          #+#    #+#             */
/*   Updated: 2019/10/16 04:14:02 by kkinzers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	write_walls(t_ed *e, int wall, int sector, int fd)
{
	while (wall <= e->s[sector].count_walls)
	{
		ft_putendl_fd(ft_itoa(e->s[sector].w[wall].v1), fd);
		ft_putendl_fd(" ", fd);
		wall++;
	}
	wall = 0;
	ft_putendl_fd("		", fd);
	while (wall < e->s[sector].count_walls)
	{
		if (wall == 0)
		{
			ft_putendl_fd(ft_itoa(e->s[sector].w[e->s[sector].count_walls].
				sosed), fd);
			ft_putendl_fd(" ", fd);
		}
		ft_putendl_fd(ft_itoa(e->s[sector].w[wall].sosed), fd);
		ft_putendl_fd(" ", fd);
		wall++;
	}
}

void	write_doors(t_ed *e, int wall, int sector, int fd)
{
	wall = 0;
	ft_putendl_fd("		", fd);
	while (wall < e->s[sector].count_walls)
	{
		if (wall == 0)
		{
			ft_putendl_fd(ft_itoa(e->s[sector].w[e->s[sector].count_walls].
				doors), fd);
			ft_putendl_fd(" ", fd);
		}
		ft_putendl_fd(ft_itoa(e->s[sector].w[wall].doors), fd);
		ft_putendl_fd(" ", fd);
		wall++;
	}
}

void	write_transparent_and_doors(t_ed *e, int wall, int sector, int fd)
{
	ft_putendl_fd("		", fd);
	while (wall < e->s[sector].count_walls)
	{
		if (wall == 0)
		{
			ft_putendl_fd(ft_itoa(e->s[sector].w[e->s[sector].count_walls].
				transparent), fd);
			ft_putendl_fd(" ", fd);
		}
		ft_putendl_fd(ft_itoa(e->s[sector].w[wall].transparent), fd);
		ft_putendl_fd(" ", fd);
		wall++;
	}
	write_doors(e, wall, sector, fd);
}

void	write_textures(t_ed *e, int wall, int sector, int fd)
{
	ft_putendl_fd("		", fd);
	while (wall < e->s[sector].count_walls)
	{
		if (wall == 0)
		{
			ft_putendl_fd(ft_itoa(e->s[sector].w[e->s[sector].count_walls].
				textures), fd);
			ft_putendl_fd(" ", fd);
		}
		ft_putendl_fd(ft_itoa(e->s[sector].w[wall].textures), fd);
		ft_putendl_fd(" ", fd);
		wall++;
	}
}

void	write_sect_to_map(t_ed *e, int fd, int sector)
{
	while (sector < e->cur_sect)
	{
		ft_putendl_fd("sector ", fd);
		ft_putendl_fd(ft_itoa(e->s[sector].floor), fd);
		ft_putendl_fd(" ", fd);
		ft_putendl_fd(ft_itoa(e->s[sector].ceil), fd);
		ft_putendl_fd(" ", fd);
		ft_putendl_fd(ft_itoa(e->s[sector].skybox), fd);
		ft_putendl_fd(" ", fd);
		ft_putendl_fd(ft_itoa(e->s[sector].naklon), fd);
		ft_putendl_fd(" ", fd);
		ft_putendl_fd(ft_itoa(e->s[sector].danger), fd);
		ft_putendl_fd(" ", fd);
		ft_putendl_fd(ft_itoa(e->s[sector].light), fd);
		ft_putendl_fd(" ", fd);
		ft_putendl_fd(ft_itoa(e->s[sector].end), fd);
		ft_putendl_fd("		", fd);
		write_walls(e, 0, sector, fd);
		write_textures(e, 0, sector, fd);
		write_transparent_and_doors(e, 0, sector, fd);
		ft_putendl_fd("\n", fd);
		sector++;
	}
}
