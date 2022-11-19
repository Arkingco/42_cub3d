/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:01:26 by kipark            #+#    #+#             */
/*   Updated: 2022/11/19 14:49:36 by kipark           ###   ########seoul.kr  */
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

static void	game_start(t_map_info *map_info)
{
	t_game	*game;

	game = ft_safe_malloc(sizeof(t_game));
	set_game(game, map_info);
	draw_game_view(game);
	mlx_put_image_to_window(game->mlx, \
									game->mlx_win, game->game_view->img, 0, 0);
	draw_mini_map(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->minimap->img, 0, 0);
	mlx_hook(game->mlx_win, EVENT_KEY_PRESS, 0, &key_press, game);
	mlx_hook(game->mlx_win, X_EVENT_EXIT, 0, &exit_window, NULL);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_map_info		map_info;

	init_map_info(&map_info, argc, argv[1]);
	game_start(&map_info);
}
