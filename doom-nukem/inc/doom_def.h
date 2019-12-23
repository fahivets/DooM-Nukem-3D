/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_def.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 12:26:55 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/15 21:29:19 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _DOOM_DEF_H
# define _DOOM_DEF_H
# define W 1600
# define H 900
# define PLAYERZ 6
# define HEADMARGIN 1
# define LEG_HEIGHT 2
# define GRAVITATION 0.05
# define PLAYERBOX 0.4
# define THREADS_C 8
# define HFOV (W / 0.9325150861)
# define VFOV (H / 2.7474774195) / 1.5
# define NEARX 0.00001
# define NEARY 0.000001
# define FARX 1
# define FARY 1.42814800674
# define DEG_35 0.610865
# define SPRITE_DELAY 200
# define MENU_TORCH_DELAY 180
# define MENU_BLOOD_DELAY 180
# define LAVA_DELAY 200
# define DOOR_DELAY 200
# define LAVA_DAMAGE_DELAY 500
# define MENU_ITEMS_COUNT 3
# define OPTIONS_ITEMS_COUNT 3
# define DIFFICULTY_ITEMS_COUNT 4
# define MIN(a, b)             (((a) < (b)) ? (a) : (b))
# define MAX(a, b)             (((a) > (b)) ? (a) : (b))
# define VCP(x0, y0, x1, y1)    ((x0) * (y1) - (x1) * (y0))
# define CLAMP(a, mi,ma) MIN(MAX(a,mi),ma)

#endif
