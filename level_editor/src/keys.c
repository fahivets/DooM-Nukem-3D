/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:14:52 by kkinzers          #+#    #+#             */
/*   Updated: 2019/10/16 20:45:21 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		sup_dot_active(t_ed *e, int i)
{
	if (e->check_pl == 0 && !fill_sector(e, i))
		return (0);
	if (e->check_pl == 1 && !player(e, i))
		return (0);
	if (e->check_pl == 2 && !start_sosed(e, i))
		return (0);
	if (e->check_pl == 3 && !start_transparent(e, i))
		return (0);
	if (e->check_pl == 4 && !start_door(e, i))
		return (0);
	if (e->check_pl == 5 && !end_lvl(e, i))
		return (0);
	return (1);
}

void	dot_active(t_ed *e, int i, int x, int y)
{
	while (++i < DOTS_H * DOTS_W)
	{
		y = -7;
		while (++y <= 6)
		{
			x = -7;
			while (++x <= 6)
				if (e->mouse_x + x == e->d[i].pos_x)
					if (e->mouse_y + y == e->d[i].pos_y)
					{
						if (!sup_dot_active(e, i))
							break ;
						else
							break ;
					}
		}
	}
}

void	sup_events2(t_ed *e)
{
	if (e->v.key.keysym.scancode == SDL_SCANCODE_E)
		if (e->number == -1)
		{
			if (e->check_pl == 0)
				e->check_pl = 5;
			else
				e->check_pl = 0;
		}
	if (e->v.key.keysym.scancode == SDL_SCANCODE_1)
		e->key_door = 1;
	if (e->v.key.keysym.scancode == SDL_SCANCODE_2)
		e->key_door = 2;
	if (e->v.key.keysym.scancode == SDL_SCANCODE_3)
		e->key_door = 3;
	if (e->v.key.keysym.scancode == SDL_SCANCODE_4)
		e->key_door = 4;
	if (e->v.key.keysym.scancode == SDL_SCANCODE_5)
		e->key_door = 5;
	if (e->v.key.keysym.scancode == SDL_SCANCODE_6)
		e->key_door = 6;
}

void	sup_events(t_ed *e)
{
	if (e->v.key.keysym.scancode == SDL_SCANCODE_S)
		if (e->number == -1)
		{
			if (e->check_pl == 0)
				e->check_pl = 2;
			else
				e->check_pl = 0;
		}
	if (e->v.key.keysym.scancode == SDL_SCANCODE_T)
		if (e->number == -1)
		{
			if (e->check_pl == 0)
				e->check_pl = 3;
			else
				e->check_pl = 0;
		}
	if (e->v.key.keysym.scancode == SDL_SCANCODE_D)
		if (e->number == -1)
		{
			if (e->check_pl == 0)
				e->check_pl = 4;
			else
				e->check_pl = 0;
		}
	sup_events2(e);
}

void	events(t_ed *e)
{
	while (SDL_PollEvent(&e->v))
	{
		if (e->v.type == SDL_MOUSEBUTTONDOWN)
			if (e->v.button.button == SDL_BUTTON_LEFT)
				dot_active(e, -1, 0, 0);
		if (e->v.type == SDL_KEYDOWN)
		{
			if (e->v.key.keysym.scancode == SDL_SCANCODE_P)
				if (e->number == -1)
				{
					if (e->check_pl == 0)
						e->check_pl = 1;
					else
						e->check_pl = 0;
				}
			sup_events(e);
			if (e->v.key.keysym.sym == SDLK_ESCAPE)
			{
				save_map(e);
				exit(0);
			}
		}
		if (e->v.type == SDL_QUIT)
			exit(0);
	}
}
