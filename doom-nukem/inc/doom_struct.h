/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 12:21:37 by asirenko          #+#    #+#             */
/*   Updated: 2019/10/16 21:20:22 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _DOOM_STRUCT_H
# define _DOOM_STRUCT_H
# include "doom_def.h"

typedef struct s_sdl	t_sdl;
typedef struct s_ixy	t_ixy;
typedef struct s_xy		t_xy;
typedef struct s_xyz	t_xyz;
typedef struct s_data	t_data;
typedef struct s_sector	t_sector;
typedef struct s_player	t_player;
typedef struct s_sprite	t_sprite;
typedef struct s_render	t_render;
typedef struct s_keys	t_keys;
typedef struct s_wall	t_wall;
typedef struct s_hud	t_hud;
typedef struct s_door	t_door;
typedef struct s_weapon	t_weapon;

struct					s_keys
{
	bool	moveup;
	bool	movedown;
	bool	moveleft;
	bool	moveright;
	bool	sit;
	bool	jump;
	bool	run;
	bool	exhaust;
};

struct					s_sdl
{
	SDL_Window	*win;

	SDL_Event	e;
	SDL_Event	m;

	TTF_Font	*menu_font;
	TTF_Font	*fps_font;
	TTF_Font	*game_font;
	TTF_Font	*hud_ammo_font;

	SDL_Surface *screen;
	SDL_Surface	*wall_textures[9];
	SDL_Surface	*wall_texture;
	SDL_Surface *sprite_tex;
	SDL_Surface	*doom_mob_tex[17];
	SDL_Surface	*floor_texture;
	SDL_Surface	*weapon_tex[2][4];
	SDL_Surface *ceil_texture;
	SDL_Surface *top_wall_texture;
	SDL_Surface *bot_wall_texture;
	SDL_Surface *lava_floor[4];
	SDL_Surface *door_tex[6][5];
	SDL_Surface *lava_ceil;
	SDL_Surface *lava_wall;
	SDL_Surface	*hud;
	SDL_Surface *menu_bg;
	SDL_Surface *fire_left;
	SDL_Surface *fire_right;
	SDL_Surface *skybox;
	SDL_Surface *transparent_wall;
	SDL_Surface *armor_tex;
	SDL_Surface *hp_potion_tex;
	SDL_Surface *medkit_tex;
	SDL_Surface	*medkit_hud;
	SDL_Surface	*key_false[6];
	SDL_Surface	*key_true[6];
	SDL_Surface	*armor_bar;
	SDL_Surface *key1;
	SDL_Surface *key2;
	SDL_Surface *key3;
	SDL_Surface *key4;
	SDL_Surface *key5;
	SDL_Surface *key6;
	SDL_Surface *ammo;
	SDL_Surface *pistol;
	SDL_Surface *menu_torch[4];
	SDL_Surface *menu_blood[8];

	Mix_Music	*menu_theme;
	Mix_Music	*game_theme;
	Mix_Chunk	*key_sound[2];
	Mix_Chunk	*steps;
	Mix_Chunk	*hit[2];
	Mix_Chunk	*voice[2];
	Mix_Chunk	*monster[2];

	t_keys		keys;

	bool		game_loop;
	bool		menu_loop;
	bool		show_fps;
	bool		options_loop;
	bool		game_started;
	bool		difficulty_loop;
	bool		language;
	bool		lvl_end;

	int			active_menu_item;
	int			active_options_item;
	int			active_difficulty_item;
	int			difficulty;

	pthread_t	tr[THREADS_C];
};

struct					s_ixy
{
	int					x;
	int					y;
};

struct					s_xy
{
	float x;
	float y;
};

struct					s_xyz
{
	float x;
	float y;
	float z;
};

struct					s_wall
{
	t_xy	v1;
	t_xy	v2;
};

struct					s_door
{
	bool	openned;
	int		keyid;
	int		frame;
	bool	full_open;
};

struct					s_sector
{
	float		floor;
	float		ceil;
	t_xy		*vertexes;
	int			*neighbors;
	char		*transparent;
	int			*textures;
	char		*doors;
	int			wall_count;
	int			sprite_count;
	int			door_count;
	bool		skybox;
	bool		danger;
	int			slope;
	float		floor_slope;
	float		ceil_slope;
	int			shade;
	bool		end;
	t_sector	*slope_nb;
	t_sprite	**sprites;
	t_door		*all_doors;
	t_wall		lwall;
	t_wall		hwall;

};

struct					s_weapon
{
	bool			have;
	int				frames;
	int				id;
	int				ammo;
	int				frame_delay;
	int				dmg_count;
	int				range;
	bool			pick_up;
};

struct					s_player
{
	t_xyz			position;
	t_weapon		weapon[10];
	float			angle;
	float			vertical_angle;
	float			anglesin;
	float			anglecos;
	int				current_sector;
	float			height;
	float			movespeed;
	bool			jumping;
	float			jumpspeed;
	int				jumpsector;
	bool			falling;
	float			fallspeed;
	int				health;
	bool			alive;
	int				ammo;
	int				armor;
	int				medkit;
	float			dx;
	float			dy;
	int				collision_count;
	bool			keys[6];
	float			stamina;
	bool			attacking;
	int				aw;
	bool			taking_lava_damage;
};

struct					s_sprite
{
	t_xyz	position;
	t_xyz	startpos;
	float	h;
	float	w;
	float	dtp;
	int		frame;
	int		sector;
	int		attack;
	bool	alive;
	bool	active;
	bool	rendered;
	bool	damaged;
	float	health;
	int		damage;
	int		type;
	int		id;
	bool	animated;
	t_xy	v1;
	t_xy	v2;
};

struct					s_data
{
	t_sector		*sectors;
	t_xy			*all_vertexes;
	t_player		player;
	t_sprite		*sprites;

	int				vertex_count;
	int				sector_count;
	int				sprite_count;

	float			**transparent_mask;
	float			dtw;
	float			sprite_dx;
	float			sprite_dy;
	t_wall			sprite_w;
	int				*topline;
	int				*bottomline;
	int				**topline_n;
	int				**bottomline_n;
	int				**left_x;
	int				count;
	int				*rendered_sectors;
	int				cs;
	int				weapon_frame;
	int				lava_frame;
	unsigned int	time_fps;
	unsigned int	time_weapon;
	unsigned int	time_sprite;
	unsigned int	time_lava_floor;
	unsigned int	time_lava_damage;
	unsigned int	current_time;
	unsigned int	time_door;
	unsigned int	frame;
	unsigned int	fps;
	int				menu_torch_frame;
	unsigned int	time_menu_torch;
	int				menu_blood_frame;
	unsigned int	time_menu_blood;
	int				spi;
	int				si;
	int				vi;
};

struct					s_render
{
	t_xy		t1;
	t_xy		t2;
	t_xy		r1;
	t_xy		r2;
	t_xy		i1;
	t_xy		i2;
	t_xy		sl1;
	t_xy		sl2;
	t_xy		old[2];
	float		angle_v1;
	float		angle_v2;
	t_xy		s1;
	t_xy		s2;
	t_xy		s3;
	t_xy		s4;
	float		s1z;
	float		s2z;
	float		s3z;
	float		s4z;
	float		zfloor;
	float		zceil;
	float		lb;
	float		la;
	int			*left_x;
	int			*right_x;
	int			*left_x_sprite;
	int			*right_x_sprite;
	float		ny1a;
	float		ny1b;
	float		ny2a;
	float		ny2b;
	float		cnya;
	float		cnyb;
	float		ceil;
	float		floor;
	float		xscale1;
	float		xscale2;
	float		yscale1;
	float		yscale2;
	float		nbceil;
	float		nbfloor;
	int			txtx;
	int			txtx_bot;
	int			txtx_top;
	int			txty;
	float		u0;
	float		u1;
	float		u0_bot;
	float		u1_bot;
	float		u0_top;
	float		u1_top;
	float		beginx;
	float		endx;
	int			ya;
	int			yb;
	int			cya;
	int			cyb;
	int			nya;
	int			nyb;
	float		floor1;
	float		floor2;
	float		ceil1;
	float		ceil2;
	float		coef_l;
	float		coef_r;
	float		z;
	bool		ceil_flag;
	t_ixy		uv;
	t_xy		map;
	t_sdl		*sdl;
	t_data		*d;
	t_sector	s;
	int			i;
	int			ii;
	t_sector	ss;
	int			current_sector;
	int			rx;
	int			lx;
	int			x;
};

struct					s_hud
{
	t_ixy				p_start;
	t_ixy				p_end;
	t_ixy				p_center;
	SDL_Color			c;
	int					old_end_x;
	int					rgb;
};

#endif
