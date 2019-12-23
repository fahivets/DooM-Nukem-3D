/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:18:11 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/16 20:47:16 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _DOOM_H
# define _DOOM_H
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/dirent.h>
# include <SDL2/SDL.h>
# include <SDL_ttf.h>
# include <SDL_image.h>
# include <SDL_mixer.h>
# include <pthread.h>
# include <stdbool.h>
# include "../lib/libft/libft.h"
# include "doom_struct.h"
# include "unpack.h"

/*
** sdl_init.c
*/

int						sdl_init(t_sdl *s);
void					sdl_close(t_sdl *s);

/*
** key_hooks.c
*/

void					key_hooks(t_sdl *sdl, t_data *d);

/*
** usage.c
*/

void					usage(void);

/*
** read_map.c
*/

void					read_map(t_data *d, t_render *r);

/*
** read_map2.c
*/

void					add_sprites_to_sector(t_data *d);

/*
** init.c
*/

void					init(t_data *d, t_sdl *sdl);
void					init_repeat(t_data *d, t_render *r);

/*
** tmp.c
*/

void					print_all_vertexes(t_data *d);
void					print_all_sectors(t_data *d);
void					print_all_sprites(t_data *d);
void					print_all_data(t_data *d);
void					print_player_data(t_data *d);

/*
** put_sector_data.c
*/

void					put_sector(char **arr, t_data *d);

/*
** calculate_map_data.c
*/

void					calculate_map_data(t_data *d);

/*
** draw.c
*/

void					draw_screen(t_sdl *sdl, t_render *r, t_data *d, int cs);
void					draw_wall(t_render *r, t_sdl *sdl);
int						apply_shade(int color, float shade_factor);

/*
** mouse_hook.c
*/

void					mouse_hook(t_data *d);

/*
** move.c
*/

void					move(t_sdl *sdl, t_data *d);

/*
** clipping.c
*/

void					clip_wall(t_render *r, t_sector s, t_sdl *sdl);

/*
** screen_projection.c
*/

void					screen_proj(t_render *r, t_data *d, t_sector s);
void					screen_proj_sprite(t_render *r, t_data *d, int i);

/*
** intersection.c
*/

t_xy					get_intersect_coord(t_xy *v, int side);
int						check_wall_intersect_with_view_lines(t_render *r);
int						intersection(t_xy *v, int side);

/*
** slopes.c
*/

void					manage_slope_sectors(t_data *d);

/*
** slopes2.c
*/

void					calc_screen_slope(t_render *r, t_sector s);
void					calc_nb_slope(t_render *r, t_data *d, t_sector s);

/*
** slope_clipping.c
*/

void					clip_left_slope(t_render *r, t_sector s);
void					clip_right_slope(t_render *r, t_sector s);

/*
** slope_move.c
*/

void					slope_move(t_data *d);
float					calc_slope_h(t_sector s, t_data *d);
float					calc_slope_h_sprite(t_sector s, t_sprite sprite);
float					distance_between_point_and_line(float x, float y,
	t_wall wall);

/*
** menu.c
*/

void					menu(t_sdl *sdl, t_data *difficulty);

/*
** menu_hooks.c
*/

void					menu_hooks(t_sdl *sdl, t_data *d);

/*
** options.c
*/

void					options(t_sdl *sdl, t_data *d);

/*
** difficulty.c
*/

void					difficulty(t_sdl *sdl, t_data *d);

/*
** difficulty_hooks.c
*/

void					choose_difficulty(t_sdl *sdl);

/*
** draw_ceil_floor.c
*/

void					draw_floor_ceil(t_render *r, t_data *d, t_sdl *sdl);

/*
** draw_divide_walls.c
*/

void					draw_divide_walls(t_render *r, t_data *d,
	t_sdl *sdl, int nb);

/*
** translate_coordinates.c
*/

void					trans_and_rot_coord(t_data *d, t_render *r,
	t_sector s, t_sdl *sdl);

/*
** threads.c
*/

void					*tread(void *param);
void					manage_treads(t_render *r, t_render *tmp,
	t_sdl *sdl, t_data *d);

/*
** sprites.c
*/

void					draw_all_sprites(t_sdl *sdl, t_data *d);

/*
** fps.c
*/

void					show_fps(t_data *data, t_sdl *sdl);

/*
** sprites_clipping.c
*/

void					clip_sprite(t_render *r, t_sdl *sdl);

/*
** sprites_translate_coordinates.c
*/

void					trans_coord_sprite(t_data *d, t_render *r,
	int i, t_sdl *sdl);

/*
** draw_hud.c
*/

void					draw_hud(t_sdl *sdl, t_data *data);
void					draw_line_on_hud(t_ixy p_start, t_ixy p_end,
	int color, t_sdl *sdl);
void					draw_hud_info(t_sdl *sdl, char *str, t_ixy pos,
	SDL_Color color);

/*
** hud_hp_bar.c
*/

void					draw_hp_bar(t_sdl *sdl, t_data *data);

/*
** hud_stamina_bar.c
*/

void					draw_stamina_bar(t_sdl *sdl, t_data *data);

/*
** sprites_animation.c
*/

void					animate_sprite(t_data *d, t_sdl *sdl);

/*
** update_sector.c
*/

void					update_sector(t_data *data);
void					update_sprite_sector(t_data *d, int i);

/*
** collision.c
*/

void					collision(t_data *d);

/*
** collision_sprite.c
*/

void					collision_sprite(t_data *d, int k);

/*
** collision2.c
*/

bool					lci(float x, float y, double r, t_wall w);
void					get_desired_motion(float *dx, float *dy, t_wall w);

/*
** timers.c
*/

void					timers(t_data *d, t_sdl *sdl);
void					menu_timer(t_data *d);

/*
** weapon.c
*/

void					draw_weapon(t_sdl *sdl, t_data *d);

/*
** hud_ammo.c
*/

void					draw_active_ammo(t_sdl *sdl, t_data *data);
void					draw_ammo_panel(t_sdl *sdl, t_data *data);

/*
** hud_items.c
*/

void					draw_hud_items(t_sdl *sdl, t_data *data);

/*
** hud_keys.c
*/

void					draw_keys(t_sdl *sdl, t_data *data);

/*
** move_sprite.c
*/

void					move_sprites(t_data *d);

/*
** skybox.c
*/

void					draw_skybox(t_sdl *sdl, t_data *d);

/*
** move2.c
*/

void					move_direction(t_sdl *sdl, t_data *d);
void					calc_move_speed(t_sdl *sdl, t_data *d);
void					sitting(t_sdl *sdl, t_data *d);
void					sprites_z_pos(t_data *d);

/*
** init_textures.c
*/

void					init_keys_texture(t_sdl *sdl);
void					init_monster_textures(t_sdl *sdl);
void					init_doors_textures(t_sdl *sdl);
void					init_menu_textures(t_sdl *sdl);

/*
** init_textures2.c
*/

void					init_weapon_textures(t_sdl *sdl);
void					init_main_textures(t_sdl *sdl);
void					init_other_textures(t_sdl *sdl);

/*
** sprites2.c
*/

void					calc_distance(t_data *d);
void					sort_sprites(t_data *d);
void					choose_sprite_texture(t_sdl *sdl, t_data *d, int i);

/*
** draw2.c
*/

void					draw_transparent_wall(t_render *r);
void					calculate_texture_x(t_render *r, float *repeat);
void					calculate_repeat(t_render *r, float *repeat);

/*
** menu_sounds.c
*/

void					play_menu_sounds(t_sdl *sdl);
void					play_key_sound(int channel, Mix_Chunk *chunk_name,
										int loops, int volume);

/*
** sounds.c
*/

void					play_game_sound(int channel, Mix_Chunk *chunk_name,
										int loops, int volume);
void					play_sounds(t_sdl *sdl, t_data *data);
void					play_game_music(t_sdl *sdl);

/*
** draw_menu.c
*/

void					draw_menu(t_sdl *sdl, t_data *data);

/*
** sprite_pick.c
*/

void					pickup_item(t_data *d, int i);

/*
** win_death.c
*/

void					win_death(t_sdl *sdl, t_data *d, t_render *r);

/*
** free_data.c
*/

void					free_all_data(t_data *d, t_render *r);
void					free_array(char **arr);

/*
** messages.c
*/

void					draw_message(t_sdl *sdl, t_data *d, int id,
	unsigned int time);

/*
** validate.c
*/

int						validate(char *fn);
void					validate_map(t_data *d);

/*
** unpack.c
*/

void					unpack(char *filename);

#endif
