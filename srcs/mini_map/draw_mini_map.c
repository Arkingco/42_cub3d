/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map->c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:38:57 by kipark            #+#    #+#             */
/*   Updated: 2022/10/13 17:16:29 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

#include<stdio.h>
static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_minimap_pixel(t_data *mini_map, int y_pixel, \
												int x_pixel, int color)
{
	int i;
	int j;

	i = y_pixel;
	while (i < y_pixel + 20)
	{
		j = x_pixel;
		while (j < x_pixel + 20)
		{
			my_mlx_pixel_put(mini_map, i, j, color);
			++j; 
		}
		++i;
	}
}

static void draw_map(t_data *mini_map, char **map)
{
	int	i;
	int	j;
	int	y_pixel;
	int	x_pixel;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			y_pixel = i * 20;
			x_pixel = j * 20;

			if (map[i][j] == '0')
				draw_minimap_pixel(mini_map, y_pixel, x_pixel, 0x00000000);
			if (map[i][j] == '1' || map[i][j] == 'P' )
				draw_minimap_pixel(mini_map, y_pixel, x_pixel, 0x000FF0FF);
			++j;
		}
		++i;
	}
}

void draw_player(t_game *game)
{
	t_player	*this_player;
	int			i;
	int			j;

	this_player = game->player;
	i = 0;
	while (i < PLAYER_SIZE)
	{
		j = 0;
		while (j < PLAYER_SIZE)
		{
			my_mlx_pixel_put(game->minimap, this_player->posX + j, \
											this_player->posY + i, 0x00FF0000);
			++j;
		}
		++i;
	}
}

#include <math.h>
int is_ray(double ray_dir, double pos, int max_size)
{
	double ret;

	ret = ray_dir + pos;
	if ((int)ret < 0 || ret > max_size)
		return (1);
	return (0);
}

void draw_ray(t_game *game)
{
	t_player *player;

	player = game->player;
	printf("start \n");
	for(int x = 0; x <= 6; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)6 - 1;
		double rayDirX = 0;
		double rayDirY = 0;
		rayDirX = player->dirX + player->planeX * cameraX / 2;
		rayDirY = player->dirY + player->planeY * cameraX / 2;
		printf("ray x : %f  y : %f\n", rayDirX, rayDirY);
		// printf("ray pow \n");
		for (int y=0; y<game->height; y++)
		{
			rayDirX += player->dirX + player->planeX * cameraX / 2;
			rayDirY += player->dirY + player->planeY * cameraX / 2;
			if(is_ray(rayDirX, player->posX, game->width) || \
						is_ray(rayDirY, player->posY, game->width))
				continue ;
			my_mlx_pixel_put(game->minimap, rayDirX + player->posX + PLAYER_SIZE / 2, \
					rayDirY + player->posY + PLAYER_SIZE / 2, 0x00FF0000);
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

void draw_mini_map(t_game *game)
{
	draw_map(game->minimap, game->map);
	draw_player(game);
	draw_ray(game);
}
