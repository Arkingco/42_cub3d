/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:23:00 by kipark            #+#    #+#             */
/*   Updated: 2022/11/18 17:09:15 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define PLAYER_SIZE 5

typedef enum e_draw_color
{
	COLOR_RED = 0x00FF0000,
	COLOR_BLUE = 0x000000FF,
	COLOR_BLACK = 0x00000000,
	COLOR_PINK = 0x00FF00FF,
	COLOR_ORANGE = 0x00DF7401
}	t_draw_color;

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
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_texture
{
	void	*east;
	t_data	*east_img;
	void	*west;
	t_data	*west_img;
	void	*south;
	t_data	*south_img;
	void	*north;
	t_data	*north_img;
}	t_texture;

typedef struct s_game
{
	char		**map;
	void		*mlx;
	void		*mlx_win;
	int			width;
	int			height;
	int			map_width;
	int			map_height;
	t_player	*player;
	t_data		*minimap;
	t_data		*game_view;
	t_texture	*texture;
	int			**texture_color;
}	t_game;

typedef struct s_ray_casting
{
	int		color;
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	perp_wall_dist;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	double	ray_point_x;
	double	ray_point_y;
}	t_ray_casting;

#endif
