# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asirenko <asirenko@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/25 15:02:32 by kkinzers          #+#    #+#              #
#    Updated: 2019/10/17 15:01:57 by asirenko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lvl_editor

LIB_H = -L ./lib
LIB_DIR = ./libft
SRCDIR	= ./src
INCDIR	= ./includes
OBJDIR	= ./obj

SRC = main.c editor.c drawmap.c drawsector.c draw_functions.c intersection.c \
		dots.c savemap.c create_sector.c check_clockwise.c sup_create_sector.c \
		savemap1.c actions.c check_cross.c keys.c sosed.c doors_transpar.c \
		pack.c custom_strings.c

SRCO = $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

HEADER = editor.h
HEADER_FLAGS = -I $(HEADER)

FLAGS = -O2 -Wall -Wextra -Werror \
 -I ~/Library/frameworks/SDL2.framework/Versions/A/Headers \
 -F ~/Library/frameworks \
 -I ~/Library/frameworks/SDL2_image.framework/Versions/A/Headers
FRAME_FLAGS = -framework SDL2 -framework SDL2_image

LIB = $(LIB_DIR)libft.a
LIB_FLAGS = -lft -L $(LIB_DIR)

all: obj $(LIB_DIR) $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(LIB):
	@make -C $(LIB_DIR)
$(NAME): $(LIB) $(SRCO)
	@gcc $(FLAGS) $(SRCO) $(LIB_FLAGS) $(FRAME_FLAGS) -o  $(NAME)
$(OBJDIR)/%.o:$(SRCDIR)/%.c
	gcc -c $(FLAGS) $< -o $@ -I $(INCDIR)
clean:
	@rm -rf $(OBJDIR)
	@make clean -C $(LIB_DIR)
fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIB_DIR)
re: fclean all
