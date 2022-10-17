/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:01:26 by kipark            #+#    #+#             */
/*   Updated: 2022/10/17 20:17:46 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "error.h"
#include "mlx.h"
#include "minimap.h"
#include "key.h"
#include <unistd.h>

void	my_mlx_pixel_pu2t(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(int argc, char *argv[])
{
	void	*mlx;
	void	*mlx_win;
	t_param	param;
	t_mini_map	mini_map;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "cub3D");
	

	// 이미지 선언 및 addr세팅
	mini_map.player.img = mlx_new_image(mlx, 10, 10);
	mini_map.player.addr = mlx_get_data_addr(mini_map.player.img, &mini_map.player.bits_per_pixel, &mini_map.player.line_length,
								&mini_map.player.endian);
	mini_map.map.img = mlx_new_image(mlx, 1200, 1200);
	mini_map.map.addr = mlx_get_data_addr(mini_map.map.img, &mini_map.map.bits_per_pixel, &mini_map.map.line_length,
								&mini_map.map.endian);
	param.map = map;
	param.mlx = mlx;
	param.mlx_win = mlx_win;
	param.mini_map = &mini_map;
	param.mini_map->player_y = 100.0;
	param.mini_map->player_x = 100.0;
	// 이미지 세팅 
	set_mini_map(&mini_map, map);
	set_mini_map_player(&mini_map);

	// 이미지 찍기
	mlx_put_image_to_window(mlx, mlx_win, mini_map.map.img, 0, 0);
	mlx_put_image_to_window(mlx, mlx_win, mini_map.player.img, param.mini_map->player_y, param.mini_map->player_x);

	mlx_hook(mlx_win, EVENT_KEY_PRESS, 0, &key_press, &param);
	mlx_hook(mlx_win, X_EVENT_EXIT, 0, &exit_window, NULL);

	mlx_loop(mlx);
}

int	main(int argc, char **argv)
{
	t_list_so_long	*str_head;
	char	**map;

	if (argc != 2)
		print_error_str("Arguments not match\n");
	str_head = NULL;
	map = parse(&str_head, argv);
	game_start(map);
}
