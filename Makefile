# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/27 15:13:41 by kipark            #+#    #+#              #
#    Updated: 2022/11/18 16:44:05 by jayoon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 						= cub3D

CC							=	cc
CFLAGS						=	-Wall -Wextra -Werror
DEBUG						=	-g -fsanitize=address
LEAKS						=	-g

LIBFT_FLAGS 				=	-L$(DIR_LIBFT) -lft
INCS_FLAGS					=	-I $(DIR_LIBFT) -I $(DIR_INCS)
LIBFT						=	$(DIR_LIBFT)/libft.a

MLXLIB 						= 	$(DIR_MLX)/libmlx.a
DIR_MLX 					= 	./minilibx_opengl_20191021
MLX_FLAGS 					= 	-L$(DIR_MLX) -lmlx -framework OpenGL -framework AppKit

DIR_SRCS					:=	./srcs
DIR_INCS 					:=	./includes
DIR_LIBFT					:=	./libft
DIR_OBJS					:=	./objs

DIR_EVENT					:=	$(DIR_SRCS)/event
DIR_ERROR					:=	$(DIR_SRCS)/error
DIR_MINI_MAP				:=	$(DIR_SRCS)/mini_map
DIR_GAME_VIEW				:=	$(DIR_SRCS)/game_view
DIR_PARSE_MAP				:=	$(DIR_SRCS)/parse_map
DIR_SET_GAME				:=	$(DIR_SRCS)/set_game

INCS						:=	cub3d.h		\
								error.h		\
								game_view.h	\
								key.h		\
								minimap.h	\
								parse_map.h	\
								struct.h
INCS						:=	$(addprefix $(DIR_INCS)/, $(INCS))

SRCS_MAIN					:=	main.c
SRCS_MAIN					:=	$(addprefix $(DIR_SRCS)/, $(SRCS_MAIN))

SRCS_PARSE_MAP				:=	init_map_info.c			\
								cub3d_atoi.c			\
								init_element.c			\
								process_color.c 		\
								process_texture_path.c	\
								init_map_content.c		\
								safe_open.c				\
								get_cnt_map_height.c	\
								get_cnt_map_width.c		\
								pass_empty_line.c		\
								pass_element.c			\
								get_map.c				\
								is_valid_map.c			\
								is_valid_character.c	\
								get_cnt.c				\
								is_start_position.c		\
								get_start_pos_info.c
SRCS_PARSE_MAP				:=	$(addprefix $(DIR_PARSE_MAP)/, $(SRCS_PARSE_MAP))

SRCS_EVENT					:=	key.c
SRCS_EVENT					:=	$(addprefix $(DIR_EVENT)/, $(SRCS_EVENT))

SRCS_MINI_MAP				:=	draw_mini_map.c			\
								draw_mini_player.c		\
								draw_mini_ray.c
SRCS_MINI_MAP				:=	$(addprefix $(DIR_MINI_MAP)/, $(SRCS_MINI_MAP))

SRCS_ERROR					:=	error.c
SRCS_ERROR					:=	$(addprefix $(DIR_ERROR)/, $(SRCS_ERROR))

SRCS_GAME_VIEW				:=	game_view.c 			\
								game_dda.c				\
								game_draw.c
SRCS_GAME_VIEW				:=	$(addprefix $(DIR_GAME_VIEW)/, $(SRCS_GAME_VIEW))

SRCS_SET_GAME				:=	set_mlx.c				\
								set_texture.c
SRCS_SET_GAME				:=	$(addprefix $(DIR_SET_GAME)/, $(SRCS_SET_GAME))

SRCS						:=	$(SRCS_MAIN)			\
								$(SRCS_EVENT)			\
								$(SRCS_ERROR)			\
								$(SRCS_PARSE_MAP)		\
								$(SRCS_MINI_MAP)		\
								$(SRCS_GAME_VIEW)		\
								$(SRCS_SET_GAME)
								
OBJS						:=	$(SRCS:.c=.o)

ifdef DEBUG_FLAG
	CFLAGS += $(DEBUG)
endif

ifdef LEAKS_FLAG
	CFLAGS += $(LEAKS)
endif

all: $(NAME)

$(NAME)		: $(LIBFT) $(MLXLIB) $(OBJS) $(INCS)
	$(CC) $(CFLAGS) $(LIBFT_FLAGS) $(MLX_FLAGS) $(OBJS) -o $@
	./cub3D asset/map_in_pdf.cub

%.o			: %.c
	$(CC) $(CFLAGS) $(INCS_FLAGS)  -c $< -o $@

$(LIBFT)	:
	make -C $(DIR_LIBFT) all

$(MLXLIB)	:
	make -C $(DIR_MLX) all

debug: 
	$(MAKE) DEBUG_FLAG=1

leaks:
	$(MAKE) LEAKS_FLAG=1

clean:
	rm -rf $(OBJS) $(NAME).dSYM
	make clean -C $(DIR_LIBFT)
	make clean -C $(DIR_MLX)

fclean:
	make clean
	make fclean -C $(DIR_LIBFT)
	make fclean -C $(DIR_MLX)
	rm -rf $(NAME)

re: 
	make fclean
	make all

.PHONY: all clean fclean re debug leaks
