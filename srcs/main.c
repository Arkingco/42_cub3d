/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:01:26 by kipark            #+#    #+#             */
/*   Updated: 2022/11/16 22:05:13 by kipark           ###   ########seoul.kr  */
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

#include <stdio.h>

static void	game_start(char **map)
{
	t_game	*game;

	game = ft_safe_malloc(sizeof(t_game));
	set_game(game, map);
	set_player(game);
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
	t_list_so_long	*str_head;
	char			**map;

	if (argc != 2)
		print_error_str("Arguments not match\n");
	str_head = NULL;
	map = parse(&str_head, argv);
	game_start(map);
}
