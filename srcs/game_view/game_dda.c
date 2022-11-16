/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_dda.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:59:38 by kipark            #+#    #+#             */
/*   Updated: 2022/11/16 22:03:23 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <struct.h>
#include <math.h>
#include "cub3d.h"
#include "libft.h"
#include "game_view.h"

static void	set_value(t_ray_casting *rc, t_player *player, t_game *game, int x)
{
	rc->camera_x = 2 * x / (double)game->width - 1;
	rc->raydir_x = player->dir_x + player->plane_x * rc->camera_x;
	rc->raydir_y = player->dir_y + player->plane_y * rc->camera_x;
	rc->map_x = (int)player->pos_x;
	rc->map_y = (int)player->pos_y;
	rc->delta_dist_x = fabs(1 / rc->raydir_x);
	rc->delta_dist_y = fabs(1 / rc->raydir_y);
	rc->hit = 0;
}

static void	set_index_distance(t_ray_casting *rc, t_player *player)
{
	if (rc->raydir_x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (player->pos_x - rc->map_x) * rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = (rc->map_x + 1.0 - player->pos_x) * rc->delta_dist_x;
	}
	if (rc->raydir_y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (player->pos_y - rc->map_y) * rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = (rc->map_y + 1.0 - player->pos_y) * rc->delta_dist_y;
	}
}

void	set_dda(t_ray_casting *rc, t_player *player, t_game *game, int x)
{
	set_value(rc, player, game, x);
	set_index_distance(rc, player);
}

void	run_dda(t_game *game, t_ray_casting *rc)
{
	while (rc->hit == 0)
	{
		if (rc->side_dist_x < rc->side_dist_y)
		{
			rc->side_dist_x += rc->delta_dist_x;
			rc->map_x += rc->step_x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			rc->map_y += rc->step_y;
			rc->side = 1;
		}
		if (game->map[rc->map_y][rc->map_x] > '0')
			rc->hit = 1;
	}
}
