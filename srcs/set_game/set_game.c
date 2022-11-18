/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:30:30 by kipark            #+#    #+#             */
/*   Updated: 2022/11/18 21:28:41 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

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

static void	malloc_game(t_game *game, t_map_info *map_info, t_data *minimap, \
															t_data *game_view)
{
	game->width = GAME_WIDTH;
	game->height = GAME_HEIGHT;
	game->map_width = map_info->map_width + 2;
	game->map_height = map_info->map_height + 2;
	game->map = map_info->map;
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, \
											game->width, game->height, "cub3D");
	game->player = ft_safe_malloc(sizeof(t_player));
	game->minimap = ft_safe_malloc(sizeof(t_data));
	game->game_view = ft_safe_malloc(sizeof(t_data));
	minimap = game->minimap;
	minimap->img = mlx_new_image(game->mlx, game->map_width * MINIMAP_SIZE, \
			game->map_height * MINIMAP_SIZE);
	minimap->addr = mlx_get_data_addr(minimap->img, \
			&minimap->bits_per_pixel, &minimap->line_length, &minimap->endian);
	game_view = game->game_view;
	game_view->img = mlx_new_image(game->mlx, game->width, game->height);
	game_view->addr = mlx_get_data_addr(game_view->img, \
	&game_view->bits_per_pixel, &game_view->line_length, &game_view->endian);
	game->texture = ft_safe_malloc(sizeof(t_texture));
	game->ceiling_info = map_info->ceiling_info;
	game->floor_info = map_info->floor_info;
}

static void	set_player_dir(t_game *game, t_map_info *map_info)
{
	if (map_info->view_direction & E)
		return ;
	else if (map_info->view_direction & W)
		rot_view(game->player, PI);
	else if (map_info->view_direction & S)
		rot_view(game->player, -(PI / 2));
	else if (map_info->view_direction & N)
		rot_view(game->player, (PI / 2));
	return ;
}

void	set_game(t_game *game, t_map_info *map_info)
{
	t_data	*minimap;
	t_data	*game_view;

	minimap = NULL;
	game_view = NULL;
	malloc_game(game, map_info, minimap, game_view);
	set_texture(game, map_info);
	set_player(game, map_info);
}

void	set_player(t_game *game, t_map_info *map_info)
{
	t_player	*this_player;

	this_player = game->player;
	this_player->pos_x = map_info->start_pos_x + 0.5;
	this_player->pos_y = map_info->start_pos_y + 0.5;
	this_player->dir_x = 1;
	this_player->dir_y = 0;
	this_player->plane_x = 0.00;
	this_player->plane_y = 0.77;
	set_player_dir(game, map_info);
}
