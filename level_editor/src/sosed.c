/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sosed.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkinzers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:17:47 by kkinzers          #+#    #+#             */
/*   Updated: 2019/10/16 17:17:48 by kkinzers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		sup_sosed(t_ed *e, int *sector, int *buf_sector)
{
	if (*sector == *buf_sector && *buf_sector != -1)
	{
		*sector += 1;
		if (*sector == e->cur_sect)
			return (0);
	}
	e->wall = -1;
	return (1);
}

void	sup_sosed1(t_ed *e, int sector, int buf_wall, int buf_sector)
{
	e->s[sector].w[e->wall].sosed = buf_sector;
	e->s[buf_sector].w[buf_wall].sosed = sector;
	e->sosed_v1 = -1;
	e->sosed_v2 = -1;
}

int		sosed(t_ed *e, int sector, int buf_wall, int buf_sector)
{
	e->check_pl = 0;
	while (sector < e->cur_sect)
	{
		e->wall = -1;
		while (++e->wall <= WALLS && buf_wall == -1 && buf_sector == -1)
			if (WV1 == e->sosed_v1 || WV2 == e->sosed_v1)
				if (WV1 == e->sosed_v2 || WV2 == e->sosed_v2)
				{
					buf_wall = e->wall;
					buf_sector = sector;
					sector = 0;
					break ;
				}
		if (!sup_sosed(e, &sector, &buf_sector))
			return (0);
		while (++e->wall <= WALLS && buf_wall != -1 && buf_sector != -1)
			if (WV1 == e->sosed_v1 || WV2 == e->sosed_v1)
				if (WV1 == e->sosed_v2 || WV2 == e->sosed_v2)
				{
					sup_sosed1(e, sector, buf_wall, buf_sector);
					return (1);
				}
		sector++;
	}
	return (0);
}

int		start_sosed(t_ed *e, int i)
{
	if (e->sosed_v1 == -1 && e->d[i].vertex_n != -1)
		e->sosed_v1 = e->d[i].vertex_n;
	else if (e->sosed_v2 == -1 && e->d[i].vertex_n != -1)
	{
		e->sosed_v2 = e->d[i].vertex_n;
		if (e->sosed_v1 == e->sosed_v2)
		{
			refresh(e);
			return (0);
		}
		if (!sosed(e, 0, -1, -1))
		{
			refresh(e);
			return (0);
		}
		return (1);
	}
	else
	{
		refresh(e);
		return (0);
	}
	return (1);
}
