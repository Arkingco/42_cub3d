# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/27 15:13:41 by kipark            #+#    #+#              #
#    Updated: 2022/10/22 18:02:09 by jayoon           ###   ########.fr        #
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

# MLXLIB 						= $(DIR_MLX)/libmlx.a
# DIR_MLX 					= ../../minilibx_opengl_20191021
# MLX_FLAGS 					= -L$(DIR_MLX) -lmlx -framework OpenGL -framework AppKit

DIR_INCS 					:=	../../includes
DIR_LIBFT					:=	../../libft

SRCS_MAIN					:=	main.c

SRCS_PARSE_MAP				:=	init_map_info.c			\
								cub3d_atoi.c

SRCS_ERROR					:=	error.c

SRCS						:=	$(SRCS_MAIN)			\
								$(SRCS_PARSE_MAP)		\
								$(SRCS_ERROR)			

OBJS						:=	$(SRCS:.c=.o)

ifdef DEBUG_FLAG
	CFLAGS += $(DEBUG)
endif

ifdef LEAKS_FLAG
	CFLAGS += $(LEAKS)
endif

all: $(NAME)

$(NAME)		: $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(LIBFT_FLAGS) $(OBJS) -o $@

%.o			: %.c
	$(CC) $(CFLAGS) $(INCS_FLAGS)  -c $< -o $@

# $(MLXLIB)	:
# 	make -C $(DIR_MLX) all

$(LIBFT)	:
	make -C $(DIR_LIBFT) all

debug: 
	$(MAKE) DEBUG_FLAG=1

leaks:
	$(MAKE) LEAKS_FLAG=1

clean:
	rm -rf $(OBJS) $(NAME).dSYM
	make clean -C $(DIR_LIBFT)
# make clean -C $(DIR_MLX)

fclean:
	make clean
	make fclean -C $(DIR_LIBFT)
	rm -f $(NAME)
# make fclean -C $(DIR_MLX)

re: 
	make fclean
	make all

.PHONY: all clean fclean re debug leaks

 