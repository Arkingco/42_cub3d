/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:38:57 by kipark            #+#    #+#             */
/*   Updated: 2022/11/16 22:06:49 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"
#include <math.h>
#include <stdio.h>
#include "game_view.h"

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_minimap_pixel(t_data *mini_map, int x_pixel, \
												int y_pixel, int color)
{
	int	i;
	int	j;

	i = y_pixel;
	while (i < y_pixel + MINIMAP_SIZE)
	{
		j = x_pixel;
		while (j < x_pixel + MINIMAP_SIZE)
		{
			my_mlx_pixel_put(mini_map, j, i, color | 0xA0000000);
			++j;
		}
		++i;
	}
}

static void	draw_map(t_data *mini_map, char **map)
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
			y_pixel = i * MINIMAP_SIZE;
			x_pixel = j * MINIMAP_SIZE;
			if (map[i][j] == '0')
				draw_minimap_pixel(mini_map, x_pixel, y_pixel, COLOR_BLACK);
			else if (map[i][j] == '1' || map[i][j] == 'P' )
				draw_minimap_pixel(mini_map, x_pixel, y_pixel, COLOR_ORANGE);
			++j;
		}
		++i;
	}
}

void	draw_mini_map(t_game *game)
{
	draw_map(game->minimap, game->map);
	draw_minimap_player(game);
	draw_minimap_ray(game);
}
