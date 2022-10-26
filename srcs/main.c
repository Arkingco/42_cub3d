/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:01:26 by kipark            #+#    #+#             */
/*   Updated: 2022/10/26 11:54:13 by kipark           ###   ########seoul.kr  */
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


#include <stdio.h>
static unsigned int	my_mlx_pixel_catch(t_data *data, int x, int y)
{
	return (*(unsigned int *)(data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8))));
}

static void set_buffer(t_game *game)
{
	game->draw_buffer = ft_safe_malloc(sizeof(int *) * game->height);
	for (int i=0; i<game->height; ++i)
		game->draw_buffer[i] = ft_safe_malloc(sizeof(int) * game->width);
}

static void set_texture(t_game *game)
{
	int img_witdh;
	int img_height;
	t_texture *texture;

	texture = game->texture;
	texture->east = mlx_xpm_file_to_image(game->mlx, "/Users/kipark/42_cub3d/srcs/img/east.xpm", &img_witdh, &img_height);
	texture->west = mlx_xpm_file_to_image(game->mlx, "/Users/kipark/42_cub3d/srcs/img/west.xpm", &img_witdh, &img_height);
	texture->south = mlx_xpm_file_to_image(game->mlx, "/Users/kipark/42_cub3d/srcs/img/south.xpm", &img_witdh, &img_height);
	texture->north = mlx_xpm_file_to_image(game->mlx, "/Users/kipark/42_cub3d/srcs/img/north.xpm", &img_witdh, &img_height);
	
	texture->east_img = ft_safe_malloc(sizeof(t_data));
	texture->west_img = ft_safe_malloc(sizeof(t_data));
	texture->south_img = ft_safe_malloc(sizeof(t_data));
	texture->north_img = ft_safe_malloc(sizeof(t_data));
	
	texture->east_img->addr = mlx_get_data_addr(texture->east, \
	&texture->east_img->bits_per_pixel, \
	&texture->east_img->line_length, &texture->east_img->endian);

	texture->west_img->addr = mlx_get_data_addr(texture->west, \
	&texture->west_img->bits_per_pixel, \
	&texture->west_img->line_length, &texture->west_img->endian);

	texture->south_img->addr = mlx_get_data_addr(texture->south, \
	&texture->south_img->bits_per_pixel, \
	&texture->south_img->line_length, &texture->south_img->endian);

	texture->north_img->addr = mlx_get_data_addr(texture->north, \
	&texture->north_img->bits_per_pixel, \
	&texture->north_img->line_length, &texture->north_img->endian);

	
	game->texture_color = ft_safe_malloc(sizeof(int *) * 8);
	for (int i=0; i<4; ++i)
		game->texture_color[i] = ft_safe_malloc(sizeof(int) * (TEX_HEIGHT * TEX_WIDTH));
	for(int y = 0; y < TEX_HEIGHT; y++)
	for(int x = 0; x < TEX_WIDTH; x++)
	{
		// 동
		game->texture_color[0][TEX_WIDTH * y + x] = my_mlx_pixel_catch(texture->east_img, x, y);
		// 서
		game->texture_color[1][TEX_WIDTH * y + x] = my_mlx_pixel_catch(texture->west_img, x, y);
		// 남
		game->texture_color[2][TEX_WIDTH * y + x] = my_mlx_pixel_catch(texture->south_img, x, y);
		// 북
		game->texture_color[3][TEX_WIDTH * y + x] = my_mlx_pixel_catch(texture->north_img, x, y);
	}

}

static void set_game(t_game *game, char **map)
{
	t_data *minimap;
	t_data *game_view;

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
	game->texture = ft_safe_malloc(sizeof(t_texture));
	set_buffer(game);
	set_texture(game);
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
	t_game	*game;

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
