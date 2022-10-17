/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:01:26 by kipark            #+#    #+#             */
/*   Updated: 2022/10/17 19:59:13 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "minimap.h"
#include "key.h"
#include <unistd.h>
#include <math.h>

	void	*mlx;
	void	*mlx_win;
	t_param	param;
	t_mini_map	mini_map;

void	my_mlx_pixel_pu2t(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
#include <stdio.h>

static void	draw_minimap()
{
	double posX = 600, posY = 200;  //x and y start position
	double dirX = -1, dirY = 0; //initial direction vector
	double planeX = 0.01, planeY = 0.00; //the 2d raycaster version of camera plane
	int	witdh = 1200;
	int height = 500;
	for(int x = 0; x < witdh; x++)
    {
		//calculate ray position and direction
		double cameraX = 2 * x / (double)witdh - 1; //x-coordinate in camera space
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		for (int y=0; y<height; y++)
		{
			rayDirX = rayDirX + cameraX * planeX;
			rayDirY += 1;
			// printf("%f     %f     %f\n", rayDirX, rayDirY, cameraX);
			my_mlx_pixel_pu2t(&mini_map.player, rayDirX + posX, \
					rayDirY + posY, 0x00FF0000);
		}
		//   int mapX = (int)posX;z	
		//   int mapY = (int)posY;

		//   //length of ray from current position to next x or y-side
		//   double sideDistX;
		//   double sideDistY; 	

		//    //length of ray from one x or y-side to next x or y-side
		//   double deltaDistX = fabs(1 / rayDirX);
		//   double deltaDistY = fabs(1 / rayDirY);
		//   double perpWallDist;

		//   //what direction to step in x or y-direction (either +1 or -1)
		//   int stepX;
		//   int stepY;

		//   int hit = 0; //was there a wall hit?
		//   int side; //was a NS or a EW wall hit?

	}
	// double time = 0; //time of current frame
	// double oldTime = 0; //time of previous frame
	  
}

static void	game_start(char **map)
{
	// void	*mlx;
	// void	*mlx_win;
	// t_param	param;
	// t_mini_map	mini_map;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "cub3D");
	

	// 이미지 선언 및 addr세팅
	mini_map.player.img = mlx_new_image(mlx, 1200, 1200);
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
	draw_minimap();
	
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
		print_error_str(EXIT_ERROR_PLAG, "Error\nArguments not match\n");
	str_head = NULL;
	map = parse(&str_head, argv);
	game_start(map);
}
