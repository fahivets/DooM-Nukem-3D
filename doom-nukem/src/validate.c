/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 14:37:47 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/16 20:55:41 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		validate(char *fn)
{
	char *ext;

	ext = ft_strrchr(fn, '.');
	if (!ext)
		return (0);
	if (ft_strcmp(ext + 1, "udt"))
		return (0);
	return (1);
}

void	validate_map(t_data *d)
{
	if (d->player.position.x < 0 || d->player.position.y < 0 ||
	d->sector_count < 1 || d->vertex_count < 4)
	{
		ft_putendl("Invalid map");
		system("rm -rf res");
		exit(0);
	}
}
