/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:59:52 by kipark            #+#    #+#             */
/*   Updated: 2022/10/14 15:03:58 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"
#include<stdio.h>


// static void	get_player_point(t_player *player, char **map)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (map[i])
// 	{
// 		j = 0;
// 		while (map[i][j])
// 		{
// 			if (map[i][j] == 'P')
// 			{
// 				player->y = i;
// 				player->x = j;
// 			}
// 			++j;
// 		}
// 		++i;
// 	}
// }

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

static void draw_minimap_pixel(t_data *player, int y_pixel, \
												int x_pixel, int color)
{
	int i;
	int j;

	i = y_pixel;
	while (i < y_pixel + 10)
	{
		j = x_pixel;
		while (j < x_pixel + 10)
		{
			my_mlx_pixel_put(player, i, j, color);
			++j;
		}
		++i;
	}
}

static void draw_player(t_data *player)
{
	draw_minimap_pixel(player, 0, 0, 0x00FF0000);
}

void	set_mini_map_player(t_mini_map *mini_map)
{
	draw_player(&mini_map->player);
}
