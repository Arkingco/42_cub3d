#
#

NAME=libmlx.a
SRC= mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m mlx_xpm.c mlx_int_str_to_wordtab.c
SRC+= mlx_png.c mlx_mouse.m
OBJ1=$(SRC:.c=.o)
OBJ=$(OBJ1:.m=.o)
CFLAGS+=-O2

# add to match string put with X11 in size and position
CFLAGS+= -DSTRINGPUTX11 -Wno-deprecated-declarations

all: $(NAME)

$(NAME):	$(OBJ)
	@ar -r $(NAME) $(OBJ)
	@ranlib $(NAME)

%.o			: %.c
	@$(CC) -c $< -o $@

clean:
	rm -f $(OBJ) *~

fclean:
	make clean
	rm -f $(NAME) mlx_app

re:
	make fclean
	make all

.PHONY: all clean fclean re
