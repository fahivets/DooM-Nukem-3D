/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 16:03:15 by kkinzers          #+#    #+#             */
/*   Updated: 2019/10/16 20:20:24 by asirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _EDITOR_H
# define _EDITOR_H
# define S_WI 2200
# define S_HE 1200
# define START_LINE 35
# define END_LINE 25
# define DOTS_H 75
# define DOTS_W 141
# define SECT_S 100
# define MIN(a,b)	(((a) < (b)) ? (a) : (b))
# define MAX(a,b)	(((a) > (b)) ? (a) : (b))
# define WV1 e->s[sector].w[e->wall].v1
# define WV2 e->s[sector].w[e->wall].v2
# define WALLS e->s[sector].count_walls
# include <SDL2/SDL.h>
# include "../libft/libft.h"
# include <fcntl.h>
# include "pack.h"

typedef	struct	s_dots
{
	double		x;
	double		y;
	double		pos_x;
	double		pos_y;
	int			active;
	int			num_in_sect;
	int			to_sect;
	int			cross;
	int			vertex;
	int			vertex_n;
	int			player;
	int			sprite;
	int			end;
}				t_dots;

typedef	struct	s_wall
{
	double		po_x1;
	double		po_y1;
	int			v1;
	double		po_x2;
	double		po_y2;
	int			v2;
	int			sosed;
	int			textures;
	int			transparent;
	int			doors;
}				t_wall;

typedef	struct	s_sector
{
	t_wall		*w;
	int			count_walls;
	double		floor;
	double		ceil;
	double		skybox;
	double		naklon;
	double		danger;
	double		light;
	double		end;
}				t_sector;

typedef	struct	s_draw
{
	double	deltax;
	double	deltay;
	double	signx;
	double	signy;
	double	error;
	double	error2;
	double	x1;
	double	y1;
	double	x2;
	double	y2;
}				t_draw;

typedef	struct	s_player
{
	int		x;
	int		y;
	int		r;
	int		sector;
}				t_player;

typedef	struct	s_inters
{
	double x1;
	double y1;
	double x2;
	double y2;
	double x3;
	double y3;
	double x4;
	double y4;
}				t_inters;

typedef	struct	s_ed
{
	SDL_Surface	*surface;
	SDL_Event	v;
	t_sector	s[SECT_S];
	t_dots		d[DOTS_H * DOTS_W];
	t_draw		dr;
	t_player	player;
	t_inters	in;
	int			i;
	int			error;
	int			number;
	int			counter;
	int			cur_sect;
	int			mouse_x;
	int			mouse_y;
	int			cir_col;
	int			line_col;
	int			per;
	double		po_x;
	double		po_y;
	int			mouse_on;
	int			check_pl;
	int			sosed_v1;
	int			sosed_v2;
	int			p_x;
	int			p_y;
	int			wall;
	int			key_door;
}				t_ed;

typedef struct	s_conv
{
	int			num;
	double		x1;
	double		y1;
	double		x2;
	double		y2;
	double		x3;
	double		y3;
	double		x4;
	double		y4;
}				t_conv;

int				main(int argc, char **argv);
void			draw_map(t_ed *e);
void			draw_sectors(t_ed *e, int c_sect, int c_wall);
void			draw_green_circle(t_ed *e, int i, int y, int radius);
void			sdl_pixel_put(t_ed *e, int x, int y, int col);
void			build_line(t_ed *e, int i, int x);
void			editor(t_ed *e);
void			line(t_ed *e);
void			events(t_ed *e);
void			write_sector(t_ed *e, int i, int l_number, int wall);
void			write_dots(t_ed *e, int i, int yi, int xi);
void			peresecheniye(t_ed *e, int i, int wall);
void			clear_dots(t_ed *e, int i);
void			check_dot_cross(t_ed *e);
void			save_map(t_ed *e);
int				fill_sector(t_ed *e, int i);
int				check_convex(t_ed *e, int j, int i);
int				intersection(t_ed *e);
void			clockwise(t_ed *e);
void			floor_ceil_skybox(t_ed *e);
int				check_one_pix(t_ed *e, int j);
void			refresh(t_ed *e);
void			write_sect_to_map(t_ed *e, int fd, int sector);
int				player(t_ed *e, int i);
int				start_sosed(t_ed *e, int i);
int				end_lvl(t_ed *e, int i);
int				start_door(t_ed *e, int i);
int				start_transparent(t_ed *e, int i);
int				sup_sosed(t_ed *e, int *sector, int *buf_sector);
void			pack(void);

#endif
