# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/27 15:13:41 by kipark            #+#    #+#              #
#    Updated: 2022/10/12 16:22:30 by kipark           ###   ########seoul.kr   #
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

MLXLIB 						= $(DIR_MLX)/libmlx.a
DIR_MLX 					= ./minilibx_opengl_20191021
MLX_FLAGS 					= -L$(DIR_MLX) -lmlx -framework OpenGL -framework AppKit

DIR_SRCS					:=	./srcs
DIR_INCS 					:=	./includes
DIR_LIBFT					:=	./libft

DIR_EVENT					:=	$(DIR_SRCS)/event
DIR_PARSER					:=	$(DIR_SRCS)/parser
DIR_ERROR					:=	$(DIR_SRCS)/error

SRCS_MAIN					:=	main.c
SRCS_MAIN					:=	$(addprefix $(DIR_SRCS)/, $(SRCS_MAIN))

SRCS_PARSER					:=	error_utils.c					\
								parse_error.c					\
								parse_utils.c					\
								parse.c
SRCS_PARSER					:=	$(addprefix $(DIR_PARSER)/, $(SRCS_PARSER))

SRCS_EVENT					:=	key_event.c	\
								key.c		\
								map.c		
SRCS_EVENT					:=	$(addprefix $(DIR_EVENT)/, $(SRCS_EVENT))

SRCS_ERROR					:=	error.c
SRCS_ERROR					:=	$(addprefix $(DIR_ERROR)/, $(SRCS_ERROR))

SRCS						:=	$(SRCS_MAIN)			\
								$(SRCS_PARSER)			\
								$(SRCS_EVENT)			\
								$(SRCS_ERROR)

OBJS						:=	$(SRCS:.c=.o)


ifdef DEBUG_FLAG
	CFLAGS += $(DEBUG)
endif

ifdef LEAKS_FLAG
	CFLAGS += $(LEAKS)
endif

all: $(NAME)

$(NAME)		: $(LIBFT) $(MLXLIB) $(OBJS) 
	$(CC) $(CFLAGS) $(LIBFT_FLAGS) $(MLX_FLAGS) $(OBJS) -o $@

%.o			: %.c
	$(CC) $(CFLAGS)  $(INCS_FLAGS)  -c $< -o $@

$(MLXLIB)	:
	make -C $(DIR_MLX) all

$(LIBFT)	:
	make -C $(DIR_LIBFT) all

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
	rm -f $(NAME) $(BONUS_NAME)

re: 
	make fclean
	make all

.PHONY: all clean fclean re debug leaks

 