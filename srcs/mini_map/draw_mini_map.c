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

#include "mlx.h"
#include "cub3d.h"
#include <stdio.h>

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_minimap_pixel(t_data *mini_map, int x_pixel, \
												int y_pixel, int color)
{
	int i;
	int j;

	i = y_pixel;
	while (i < y_pixel + 20)
	{
		j = x_pixel;
		while (j < x_pixel + 20)
		{
			my_mlx_pixel_put(mini_map, j, i, color);
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
				draw_minimap_pixel(mini_map, x_pixel, y_pixel, COLOR_BLACK);
			else if (map[i][j] == '1' || map[i][j] == 'P' )
				draw_minimap_pixel(mini_map, x_pixel, y_pixel, COLOR_ORANGE);
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
			my_mlx_pixel_put(game->minimap, this_player->posX * 20 + j, \
											this_player->posY * 20 + i, COLOR_RED);
			++j;
		}
		++i;
	}
}

#include <math.h>
int is_ray(double ray_size, int max_size)
{
	if (ray_size < 0 || ray_size > max_size)
		return (1);
	return (0);
}

void draw_ray(t_game *game)
{
	t_player *player;

	player = game->player;
	for(int x = 0; x <= 60; x++)
	{
		double cameraX = 2 * x / (double)60 - 1;
		double rayDirX = 0;
		double rayDirY = 0;
		rayDirX = player->dirX + player->planeX * cameraX / 2;
		rayDirY = player->dirY + player->planeY * cameraX / 2;
		for (int y=0; y<game->mini_height * 30; y++)
		{
			rayDirX += player->dirX + player->planeX * cameraX / 2;
			rayDirY += player->dirY + player->planeY * cameraX / 2;
			if(is_ray(rayDirX + (player->posX * 20) + PLAYER_SIZE / 2, game->mini_width * 20) || \
				is_ray(rayDirY + (player->posY * 20) + PLAYER_SIZE / 2, game->mini_height * 20))
				continue ;
			my_mlx_pixel_put(game->minimap, rayDirX + (player->posX * 20) + PLAYER_SIZE / 2, \
					rayDirY + (player->posY * 20) + PLAYER_SIZE / 2, 0x00FF0000);
		}
	}
}

void draw_mini_map(t_game *game)
{
	draw_map(game->minimap, game->map);
	draw_player(game);
	draw_ray(game);
}
