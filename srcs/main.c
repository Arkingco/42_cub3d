/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:01:26 by kipark            #+#    #+#             */
/*   Updated: 2022/10/13 19:38:49 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"
#include "minimap.h"
#include <unistd.h>

void	my_mlx_pixel_pu2t(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

static void	game_start(char **map)
{
	void	*mlx;
	void	*mlx_win;
	// t_param	param;
	t_data	mini_map;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "cub3D");
	// mlx_hook(mlx_win, EVENT_KEY_PRESS, 0, &key_press, &param);
	// mlx_hook(mlx_win, X_EVENT_EXIT, 0, &exit_window, NULL);

	mini_map.img = mlx_new_image(mlx, 1200, 1200);
	mini_map.addr = mlx_get_data_addr(mini_map.img, &mini_map.bits_per_pixel, &mini_map.line_length,
								&mini_map.endian);
	set_mini_map(&mini_map, map);
	mlx_put_image_to_window(mlx, mlx_win, mini_map.img, 0, 0);
	mlx_put_image_to_window(mlx, mlx_win, mini_map.img, 0, 0);

	mlx_loop(mlx);
}

int	main(int argc, char **argv)
{
	t_list	*str_head;
	char	**map;

	if (argc != 2)
		print_error_str(EXIT_ERROR_PLAG, "Error\nArguments not match\n");
	str_head = NULL;
	map = parse(&str_head, argv);
	game_start(map);
}
