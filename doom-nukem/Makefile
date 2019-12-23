# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/01 17:16:17 by asirenko          #+#    #+#              #
#    Updated: 2019/10/17 22:05:00 by dsamarsk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem

SRC_DIR = ./src/
OBJ_DIR = ./obj/
INC_DIR = ./inc/
LIB_DIR = ./lib/
HEADERS = $(INC_DIR)doom.h $(INC_DIR)get_next_line.h

SRC =	main.c \
		sdl_init.c \
		key_hooks.c \
		read_map.c \
		read_map2.c \
		usage.c \
		init.c \
		put_sector_data.c \
		calculate_map_data.c \
		draw.c \
		mouse_hook.c \
		move.c \
		screen_projection.c \
		clipping.c \
		intersection.c \
		slopes.c \
		slopes2.c \
		slope_clipping.c \
		slope_move.c \
		menu.c \
		menu_hooks.c \
		options.c \
		draw_ceil_floor.c \
		draw_divide_walls.c \
		translate_coordinates.c \
		threads.c \
		sprites.c \
		sprites_clipping.c \
		draw_hud.c \
		difficulty.c \
		difficulty_hooks.c \
		fps.c \
		sprites_translate_coordinates.c \
		hud_hp_bar.c \
		hud_stamina_bar.c \
		sprites_animation.c \
		update_sector.c \
		collision.c \
		timer.c \
		weapon.c \
		hud_ammo.c \
		hud_items.c \
		hud_keys.c \
		move_sprite.c \
		collision_sprite.c \
		collision2.c \
		skybox.c \
		move2.c \
		init_textures.c \
		init_textures2.c \
		sprites2.c \
		draw2.c \
		draw_menu.c \
		sounds.c \
		sprite_pick.c \
		win_death.c \
		free_data.c \
		menu_sounds.c \
		validate.c \
		unpack.c \
		parse.c \

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

CC = gcc -g -Wall -Wextra -Werror -O2\
	-I Frameworks/SDL2.framework/Versions/A/Headers \
	-F Frameworks/ \
	-I Frameworks/SDL2_ttf.framework/Versions/A/Headers \
	-F Frameworks/ \
	-I Frameworks/SDL2_image.framework/Versions/A/Headers \
	-F Frameworks/ \
	-I Frameworks/SDL2_mixer.framework/Versions/A/Headers \
	-F Frameworks/

FLAGS = -rpath Frameworks/ \
		-framework SDL2 \
		-framework SDL2_ttf \
		-framework SDL2_image \
		-framework SDL2_mixer

LIBFT_DIR = $(LIB_DIR)libft/
LIBFT = $(LIBFT_DIR)libft.a

all:  $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@make -C $(LIBFT_DIR)
	@$(CC) $(LIBFT) $(OBJ) $(FLAGS) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	
$(OBJ_DIR)%.o: %.c
	$(CC) -c $< -o $@ -I $(INC_DIR)

clean:
	/bin/rm -rf $(OBJ)
	/bin/rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

vpath %.c $(SRC_DIR)
