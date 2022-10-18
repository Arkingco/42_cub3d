/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:23:00 by kipark            #+#    #+#             */
/*   Updated: 2022/10/18 19:55:49 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#define PLAYER_SIZE 5

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
	t_player	*player;
	t_data		*minimap;
}	t_game;


#endif
