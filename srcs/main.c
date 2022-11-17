/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:01:26 by kipark            #+#    #+#             */
/*   Updated: 2022/11/17 18:40:03 by jayoon           ###   ########.fr       */
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

static void	free_all(t_map_info *map_info)
{
	size_t	i;

	i = 0;
	while (i < CNT_TEXTURE)
	{
		ft_safe_free(map_info->texture_path[i]);
		++i;
	}
	ft_safe_free_two_dimentions_arr(map_info->map);
}

static void	game_start(t_map_info *map_info)
{
	t_game	*game;

	game = ft_safe_malloc(sizeof(t_game));
	set_game(game, map_info);
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
	t_map_info		map_info;

	str_head = NULL;
	init_map_info(&map_info, argc, argv[1]);
	game_start(&map_info);
	free_all(&map_info);
}
