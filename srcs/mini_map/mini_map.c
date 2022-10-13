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


void	get_player_point(t_player *player, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
			{
				player->y = i;
				player->x = j;
			}
			++j;
		}
		++i;
	}
}

#include<stdio.h>
void draw_minimap_pixel(t_data *mini_map, int y_pixel, \
												int x_pixel, int color)
{
	int i;
	int j;
	int count;

	count = 0;
	i = y_pixel;
	j = x_pixel;
	y_pixel = y_pixel + 40;
	x_pixel = x_pixel + 40;
	while (i < y_pixel)
	{
		while (j < x_pixel)
		{
			printf("in here %d %d %d %d %d\n", i, j, count, y_pixel, x_pixel);
			count++;
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

	for (int j=0; map[j] != NULL; ++j)
		printf("%s\n", map[j]);
	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			y_pixel = i * 40;
			x_pixel = j * 40;
			printf("%d %d %c\n", i, j, map[i][j]);
			if (map[i][j] == 'P')
				draw_minimap_pixel(mini_map, y_pixel, x_pixel, 0x00FF0000);
			else if (map[i][j] == '0')
				draw_minimap_pixel(mini_map, y_pixel, x_pixel, 0x00FFFF00);
			else if (map[i][j] == '1')
				draw_minimap_pixel(mini_map, y_pixel, x_pixel, 0x000FF0FF);
			++j;
		}
		++i;
	}
	j = 0;
	printf("%d %d \n", i, j);
}

void set_mini_map(t_data *mini_map, char **map)
{
	// t_player	player;

	// get_player_point(&player, map);
	draw_minimap(mini_map, map);
}
