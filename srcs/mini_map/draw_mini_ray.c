/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:09:58 by kipark            #+#    #+#             */
/*   Updated: 2022/11/16 22:03:23 by kipark           ###   ########seoul.kr  */
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

int	is_ray(double ray_point_x, double ray_point_y, t_game *game)
{
	if (ray_point_x < 0 || ray_point_x > game->mini_width * MINI_SIZE || \
			ray_point_y < 0 || ray_point_y > game->mini_height * MINI_SIZE || \
			(int)ray_point_x / MINI_SIZE < 0 || \
			(int)ray_point_x / MINI_SIZE > game->mini_width - 1 || \
			(int)ray_point_y / MINI_SIZE < 0 || \
			(int)ray_point_y / MINI_SIZE > game->mini_height - 1 || \
			game->map[(int)ray_point_y / \
								MINI_SIZE][(int)ray_point_x / MINI_SIZE] == '1')
		return (1);
	return (0);
}

void	draw_ray(t_game *game, t_ray_casting *rc, t_player *player)
{
	int	y;

	y = 0;
	while (y < (int)game->width)
	{
		rc->raydir_x += player->dir_x + player->plane_x * rc->camera_x;
		rc->raydir_y += player->dir_y + player->plane_y * rc->camera_x;
		rc->ray_point_x = rc->raydir_x + (player->pos_x * MINI_SIZE) + \
														PLAYER_SIZE / 2;
		rc->ray_point_y = rc->raydir_y + (player->pos_y * MINI_SIZE) + \
														PLAYER_SIZE / 2;
		if (is_ray(rc->ray_point_x, rc->ray_point_y, game))
		{
			y = (int)game->width;
			continue ;
		}
		my_mlx_pixel_put(game->minimap, rc->ray_point_x, \
											rc->ray_point_y, 0x00FF0000);
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
