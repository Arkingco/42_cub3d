/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:30:30 by kipark            #+#    #+#             */
/*   Updated: 2022/11/16 22:03:23 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "error.h"
#include "mlx.h"
#include "key.h"
#include "libft.h"
#include "cub3d.h"
#include "minimap.h"
#include "game_view.h"
#include <unistd.h>
#include <math.h>

void	set_game(t_game *game, char **map)
{
	t_data	*minimap;
	t_data	*game_view;

	game->width = 1500;
	game->height = 1000;
	game->mini_width = 50;
	game->mini_height = 10;
	game->map = map;
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, \
											game->width, game->height, "cub3D");
	game->player = ft_safe_malloc(sizeof(t_player));
	game->minimap = ft_safe_malloc(sizeof(t_data));
	game->game_view = ft_safe_malloc(sizeof(t_data));
	minimap = game->minimap;
	minimap->img = \
		mlx_new_image(game->mlx, game->mini_width * 20, game->mini_height * 20);
	minimap->addr = mlx_get_data_addr(minimap->img, \
			&minimap->bits_per_pixel, &minimap->line_length, &minimap->endian);
	game_view = game->game_view;
	game_view->img = mlx_new_image(game->mlx, game->width, game->height);
	game_view->addr = mlx_get_data_addr(game_view->img, \
	&game_view->bits_per_pixel, &game_view->line_length, &game_view->endian);
	game->texture = ft_safe_malloc(sizeof(t_texture));
	set_texture(game);
}

void	set_player(t_game *game)
{
	t_player	*this_player;

	this_player = game->player;
	this_player->pos_x = 1.5;
	this_player->pos_y = 1.5;
	this_player->dir_x = 1;
	this_player->dir_y = 0;
	this_player->plane_x = 0.00;
	this_player->plane_y = 0.77;
}
