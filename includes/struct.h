/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:23:00 by kipark            #+#    #+#             */
/*   Updated: 2022/10/22 17:48:57 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#define PLAYER_SIZE 5
#define MINI_SIZE 20
typedef enum e_draw_color
{
	COLOR_RED = 0x00FF0000,
	COLOR_BLUE = 0x000000FF,
	COLOR_BLACK = 0x00000000,
	COLOR_PINK = 0x00FF00FF,
	COLOR_ORANGE = 0x00DF7401
} t_draw_color;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_player
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
}	t_player;

typedef struct s_list_so_long
{
	char			*str;
	struct s_list_so_long	*next;
}				t_list_so_long;

typedef struct s_game
{
	char		**map;
	void		*mlx;
	void		*mlx_win;
	int			width;
	int			height;
	int			mini_width;
	int			mini_height;
	t_player	*player;
	t_data		*minimap;
	t_data		*game_view;
}	t_game;

typedef struct s_dda
{
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	perpWallDist;
	double	deltaDistX;
	double	deltaDistY;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
}	t_dda;

#endif
