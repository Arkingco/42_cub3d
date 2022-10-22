/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:01:26 by kipark            #+#    #+#             */
/*   Updated: 2022/10/22 18:59:29 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "key.h"
#include "libft.h"
#include "cub3d.h"
#include "minimap.h"
#include "game_view.h"
#include <unistd.h>
#include <math.h>

static void set_game(t_game *game, char **map)
{
	t_data *minimap;
	t_data *game_view;

	// map 도 임의로 지정 해줘야함
	game->width = 1500;
	game->height = 1000;
	game->mini_width = 50;
	game->mini_height = 10;
	game->map = map;
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, game->width, game->height, "cub3D");
	game->player = ft_safe_malloc(sizeof(t_player));
	game->minimap = ft_safe_malloc(sizeof(t_data));
	game->game_view = ft_safe_malloc(sizeof(t_data));
	minimap = game->minimap;
	minimap->img = mlx_new_image(game->mlx, game->mini_width * 20, game->mini_height * 20);
	minimap->addr = mlx_get_data_addr(minimap->img, \
			&minimap->bits_per_pixel, &minimap->line_length, &minimap->endian);
	game_view = game->game_view;
	game_view->img = mlx_new_image(game->mlx, game->width, game->height);
	game_view->addr = mlx_get_data_addr(game_view->img, \
	&game_view->bits_per_pixel, &game_view->line_length, &game_view->endian);
}

static void	set_player(t_game *game)
{
	t_player *this_player;

	this_player = game->player; 
	// 이 부분은 따로 P의 위치를 찾는 로직을 넣어야함 	
	this_player->posX = 1.5;
	this_player->posY = 1.5;
	this_player->dirX = 1;
	this_player->dirY = 0; //initial direction vector
	this_player->planeX = 0.00;
	this_player->planeY = 0.77; // the 2d raycaster version of camera plane
}

static void	game_start(char **map)
{
	t_game *game;

	game = ft_safe_malloc(sizeof(t_game));
	set_game(game, map);
	set_player(game);

	draw_game_view(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->game_view->img, 0, 0);
	draw_mini_map(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->minimap->img, 0, 0);
	
	mlx_hook(game->mlx_win, EVENT_KEY_PRESS, 0, &key_press, game);
	mlx_hook(game->mlx_win, X_EVENT_EXIT, 0, &exit_window, NULL);
	
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_list_so_long	*str_head;
	char	**map;

	if (argc != 2)
		print_error_str(EXIT_ERROR_PLAG, "Error\nArguments not match\n");
	str_head = NULL;
	map = parse(&str_head, argv);
	game_start(map);
}
