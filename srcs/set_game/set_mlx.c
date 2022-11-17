/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:30:30 by kipark            #+#    #+#             */
/*   Updated: 2022/11/17 18:55:44 by jayoon           ###   ########.fr       */
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
#include "parse_map.h"
#include <unistd.h>
#include <math.h>

void	set_game(t_game *game, t_map_info *map_info)
{
	t_data	*minimap;
	t_data	*game_view;

	game->width = GAME_WIDTH;
	game->height = GAME_HEIGHT;
	game->mini_width = map_info->map_width + 2;
	game->mini_height = map_info->map_height + 2;
	game->map = map_info->map;
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, \
											game->width, game->height, "cub3D");
	game->player = ft_safe_malloc(sizeof(t_player));
	game->minimap = ft_safe_malloc(sizeof(t_data));
	game->game_view = ft_safe_malloc(sizeof(t_data));
	minimap = game->minimap;
	minimap->img = mlx_new_image(game->mlx, game->mini_width * MINIMAP_SIZE, \
			game->mini_height * MINIMAP_SIZE);
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
	this_player->pos_x = 11.5;
	this_player->pos_y = 2.5;
	this_player->dir_x = 1;
	this_player->dir_y = 0;
	this_player->plane_x = 0.00;
	this_player->plane_y = 0.77;
}
