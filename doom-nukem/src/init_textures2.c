/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:41:24 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/16 22:33:04 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_weapon_textures(t_sdl *sdl)
{
	sdl->weapon_tex[0][0] = IMG_Load("res/weapon1_1.png");
	sdl->weapon_tex[0][1] = IMG_Load("res/weapon1_2.png");
	sdl->weapon_tex[0][2] = IMG_Load("res/weapon1_3.png");
	sdl->weapon_tex[0][3] = IMG_Load("res/weapon1_1.png");
	sdl->weapon_tex[1][0] = IMG_Load("res/weapon2_1.png");
	sdl->weapon_tex[1][1] = IMG_Load("res/weapon2_2.png");
	sdl->weapon_tex[1][2] = IMG_Load("res/weapon2_3.png");
	sdl->weapon_tex[1][3] = IMG_Load("res/weapon2_4.png");
	sdl->ammo = IMG_Load("res/ammo.png");
	sdl->pistol = IMG_Load("res/pistol.png");
}

void	init_main_textures(t_sdl *sdl)
{
	sdl->wall_textures[0] = IMG_Load("res/wall.png");
	sdl->wall_textures[1] = IMG_Load("res/wall_2.png");
	sdl->wall_textures[2] = IMG_Load("res/wall_3.png");
	sdl->wall_textures[3] = IMG_Load("res/wall_4.png");
	sdl->wall_textures[4] = IMG_Load("res/wall_5.png");
	sdl->wall_textures[5] = IMG_Load("res/wall_6.png");
	sdl->wall_textures[6] = IMG_Load("res/wall_7.png");
	sdl->wall_textures[7] = IMG_Load("res/wall_8.png");
	sdl->wall_textures[8] = IMG_Load("res/wall_9.png");
	sdl->transparent_wall = IMG_Load("res/transparent_wall.png");
	sdl->floor_texture = IMG_Load("res/floor.png");
	sdl->ceil_texture = IMG_Load("res/ceil.png");
	sdl->top_wall_texture = IMG_Load("res/top_wall.png");
	sdl->bot_wall_texture = IMG_Load("res/bot_wall.png");
	sdl->lava_floor[0] = IMG_Load("res/lava_floor1.png");
	sdl->lava_floor[1] = IMG_Load("res/lava_floor2.png");
	sdl->lava_floor[2] = IMG_Load("res/lava_floor3.png");
	sdl->lava_floor[3] = IMG_Load("res/lava_floor4.png");
	sdl->lava_ceil = IMG_Load("res/lava_ceil.png");
	sdl->lava_wall = IMG_Load("res/lava_wall.png");
}

void	init_other_textures(t_sdl *sdl)
{
	sdl->hud = IMG_Load("res/hud.png");
	sdl->medkit_hud = IMG_Load("res/medkit_90x93.png");
	sdl->fire_left = IMG_Load("res/fire_left.png");
	sdl->fire_right = IMG_Load("res/fire_right.png");
	sdl->skybox = IMG_Load("res/skybox.png");
	sdl->armor_tex = IMG_Load("res/armor.png");
	sdl->hp_potion_tex = IMG_Load("res/hp_potion.png");
	sdl->medkit_tex = IMG_Load("res/medkit.png");
	sdl->armor_bar = IMG_Load("res/armor_bar.png");
}
