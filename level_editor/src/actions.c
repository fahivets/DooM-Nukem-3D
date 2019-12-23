/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkinzers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:01:11 by kkinzers          #+#    #+#             */
/*   Updated: 2019/10/16 16:01:12 by kkinzers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		player(t_ed *e, int i)
{
	e->check_pl = 0;
	if (e->d[i].player == 1)
	{
		e->player.x = 0;
		e->player.y = 0;
		e->player.sector = 0;
		e->player.r = 0;
		e->d[i].player = 0;
		return (0);
	}
	if (e->player.x > 0)
		return (0);
	if (e->d[i].to_sect == 9999)
		return (0);
	if (e->d[i].vertex == 1)
		return (0);
	e->player.x = e->d[i].x;
	e->player.y = e->d[i].y;
	e->player.sector = e->d[i].to_sect;
	e->player.r = 0;
	e->d[i].player = 1;
	return (1);
}

void	refresh(t_ed *e)
{
	e->sosed_v1 = -1;
	e->sosed_v2 = -1;
	e->check_pl = 0;
}
