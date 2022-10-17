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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

#include<stdio.h>
void draw_minimap_pixel(t_data *mini_map, int y_pixel, \
												int x_pixel, int color)
{
	int i;
	int j;

	i = y_pixel;
	while (i < y_pixel + 40)
	{
		j = x_pixel;
		while (j < x_pixel + 40)
		{
			my_mlx_pixel_put(mini_map, i, j, color);
			++j; 
		}
		++i;
	}
}

void draw_minimap(t_data *mini_map, char **map)
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
			y_pixel = i * 40;
			x_pixel = j * 40;
			// if (map[i][j] == '0')
			// 	draw_minimap_pixel(mini_map, y_pixel, x_pixel, 0x00000000);
			if (map[i][j] == '1')
				draw_minimap_pixel(mini_map, y_pixel, x_pixel, 0x000FF0FF);
			++j;
		}
		++i;
	}
	j = 0;
}

void set_mini_map(t_mini_map *mini_map, char **map)
{
	draw_minimap(&mini_map->map, map);
}
