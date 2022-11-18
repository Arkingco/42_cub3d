/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:09:58 by kipark            #+#    #+#             */
/*   Updated: 2022/11/18 18:57:18 by kipark           ###   ########seoul.kr  */
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

static unsigned int	my_mlx_pixel_catch(t_data *data, int x, int y)
{
	return (*(unsigned int *)(data->addr + \
					y * data->line_length + x * (data->bits_per_pixel / 8)));
}

int	is_ray(double ray_point_x, double ray_point_y, t_game *game)
{
	if (my_mlx_pixel_catch(game->minimap, ray_point_x, ray_point_y) \
									== (COLOR_ORANGE | 0xA0000000) || \
		my_mlx_pixel_catch(game->minimap, ray_point_x + 1, ray_point_y + 1) \
									== (COLOR_ORANGE | 0xA0000000) || \
		my_mlx_pixel_catch(game->minimap, ray_point_x - 1, ray_point_y - 1) \
									== (COLOR_ORANGE | 0xA0000000))
		return (1);
	return (0);
}

void	draw_ray(t_game *game, t_ray_casting *rc, t_player *player)
{
	int	y;

	y = 0;
	while (y < (int)game->width * 2)
	{
		rc->raydir_x += player->dir_x + player->plane_x * rc->camera_x;
		rc->raydir_y += player->dir_y + player->plane_y * rc->camera_x;
		rc->ray_point_x = rc->raydir_x + (player->pos_x * MINIMAP_SIZE);
		rc->ray_point_y = rc->raydir_y + (player->pos_y * MINIMAP_SIZE);
		if (is_ray(rc->ray_point_x, rc->ray_point_y, game))
		{
			y = (int)game->width * 2;
			continue ;
		}
		my_mlx_pixel_put(game->minimap, rc->ray_point_x, \
									rc->ray_point_y, COLOR_RED | 0xA0000000);
		++y;
	}
}

void	draw_minimap_ray(t_game *game)
{
	t_player		*player;
	t_ray_casting	rc;
	int				x;

	player = game->player;
	x = 0;
	while (x < game->width)
	{
		rc.camera_x = 2 * x / (double)game->width - 1;
		rc.raydir_x = 0;
		rc.raydir_y = 0;
		draw_ray(game, &rc, player);
		++x;
	}
}
