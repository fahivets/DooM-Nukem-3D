/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:39:35 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/16 14:30:41 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		init_menu_textures(t_sdl *sdl)
{
	sdl->menu_bg = IMG_Load("res/menu_bg.png");
	sdl->menu_torch[0] = IMG_Load("res/menu_torch_0.png");
	sdl->menu_torch[1] = IMG_Load("res/menu_torch_1.png");
	sdl->menu_torch[2] = IMG_Load("res/menu_torch_2.png");
	sdl->menu_torch[3] = IMG_Load("res/menu_torch_3.png");
	sdl->menu_blood[0] = IMG_Load("res/menu_blood_0.png");
	sdl->menu_blood[1] = IMG_Load("res/menu_blood_1.png");
	sdl->menu_blood[2] = IMG_Load("res/menu_blood_2.png");
	sdl->menu_blood[3] = IMG_Load("res/menu_blood_3.png");
	sdl->menu_blood[4] = IMG_Load("res/menu_blood_4.png");
	sdl->menu_blood[5] = IMG_Load("res/menu_blood_5.png");
	sdl->menu_blood[6] = IMG_Load("res/menu_blood_6.png");
	sdl->menu_blood[7] = IMG_Load("res/menu_blood_7.png");
}

void		init_keys_texture(t_sdl *sdl)
{
	sdl->key_false[0] = IMG_Load("res/key_false_0.png");
	sdl->key_false[1] = IMG_Load("res/key_false_1.png");
	sdl->key_false[2] = IMG_Load("res/key_false_2.png");
	sdl->key_false[3] = IMG_Load("res/key_false_3.png");
	sdl->key_false[4] = IMG_Load("res/key_false_4.png");
	sdl->key_false[5] = IMG_Load("res/key_false_5.png");
	sdl->key_true[0] = IMG_Load("res/key_true_0.png");
	sdl->key_true[1] = IMG_Load("res/key_true_1.png");
	sdl->key_true[2] = IMG_Load("res/key_true_2.png");
	sdl->key_true[3] = IMG_Load("res/key_true_3.png");
	sdl->key_true[4] = IMG_Load("res/key_true_4.png");
	sdl->key_true[5] = IMG_Load("res/key_true_5.png");
	sdl->key1 = IMG_Load("res/key1.png");
	sdl->key2 = IMG_Load("res/key2.png");
	sdl->key3 = IMG_Load("res/key3.png");
	sdl->key4 = IMG_Load("res/key4.png");
	sdl->key5 = IMG_Load("res/key5.png");
	sdl->key6 = IMG_Load("res/key6.png");
}

void		init_monster_textures(t_sdl *sdl)
{
	sdl->doom_mob_tex[0] = IMG_Load("res/mob1.png");
	sdl->doom_mob_tex[1] = IMG_Load("res/mob2.png");
	sdl->doom_mob_tex[2] = IMG_Load("res/mob3.png");
	sdl->doom_mob_tex[3] = IMG_Load("res/mob4.png");
	sdl->doom_mob_tex[4] = IMG_Load("res/mob5.png");
	sdl->doom_mob_tex[5] = IMG_Load("res/mob6.png");
	sdl->doom_mob_tex[6] = IMG_Load("res/mob7.png");
	sdl->doom_mob_tex[7] = IMG_Load("res/mob8.png");
	sdl->doom_mob_tex[8] = IMG_Load("res/mob9.png");
	sdl->doom_mob_tex[9] = IMG_Load("res/mob10.png");
	sdl->doom_mob_tex[10] = IMG_Load("res/mob11.png");
	sdl->doom_mob_tex[11] = IMG_Load("res/mob12.png");
	sdl->doom_mob_tex[12] = IMG_Load("res/mob13.png");
	sdl->doom_mob_tex[13] = IMG_Load("res/mob14.png");
	sdl->doom_mob_tex[14] = IMG_Load("res/mob15.png");
	sdl->doom_mob_tex[15] = IMG_Load("res/mob16.png");
	sdl->doom_mob_tex[16] = IMG_Load("res/mob17.png");
}

static void	init_doors_textures2(t_sdl *sdl)
{
	sdl->door_tex[3][0] = IMG_Load("res/door4_1.png");
	sdl->door_tex[3][1] = IMG_Load("res/door4_2.png");
	sdl->door_tex[3][2] = IMG_Load("res/door4_3.png");
	sdl->door_tex[3][3] = IMG_Load("res/door4_4.png");
	sdl->door_tex[3][4] = IMG_Load("res/door4_5.png");
	sdl->door_tex[4][0] = IMG_Load("res/door5_1.png");
	sdl->door_tex[4][1] = IMG_Load("res/door5_2.png");
	sdl->door_tex[4][2] = IMG_Load("res/door5_3.png");
	sdl->door_tex[4][3] = IMG_Load("res/door5_4.png");
	sdl->door_tex[4][4] = IMG_Load("res/door5_5.png");
	sdl->door_tex[5][0] = IMG_Load("res/door6_1.png");
	sdl->door_tex[5][1] = IMG_Load("res/door6_2.png");
	sdl->door_tex[5][2] = IMG_Load("res/door6_3.png");
	sdl->door_tex[5][3] = IMG_Load("res/door6_4.png");
	sdl->door_tex[5][4] = IMG_Load("res/door6_5.png");
}

void		init_doors_textures(t_sdl *sdl)
{
	sdl->door_tex[0][0] = IMG_Load("res/door1_1.png");
	sdl->door_tex[0][1] = IMG_Load("res/door1_2.png");
	sdl->door_tex[0][2] = IMG_Load("res/door1_3.png");
	sdl->door_tex[0][3] = IMG_Load("res/door1_4.png");
	sdl->door_tex[0][4] = IMG_Load("res/door1_5.png");
	sdl->door_tex[1][0] = IMG_Load("res/door2_1.png");
	sdl->door_tex[1][1] = IMG_Load("res/door2_2.png");
	sdl->door_tex[1][2] = IMG_Load("res/door2_3.png");
	sdl->door_tex[1][3] = IMG_Load("res/door2_4.png");
	sdl->door_tex[1][4] = IMG_Load("res/door2_5.png");
	sdl->door_tex[2][0] = IMG_Load("res/door3_1.png");
	sdl->door_tex[2][1] = IMG_Load("res/door3_2.png");
	sdl->door_tex[2][2] = IMG_Load("res/door3_3.png");
	sdl->door_tex[2][3] = IMG_Load("res/door3_4.png");
	sdl->door_tex[2][4] = IMG_Load("res/door3_5.png");
	init_doors_textures2(sdl);
}
