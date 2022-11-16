/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:53:10 by kipark            #+#    #+#             */
/*   Updated: 2022/11/16 22:05:38 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "key.h"
#include "mlx.h"
#include "cub3d.h"
#include "minimap.h"
#include "game_view.h"
#include <math.h>
#include <stdlib.h>

static void	rot_view(t_player *player, double rot)
{
	double	olddir;
	double	oldplane;

	olddir = player->dir_y;
	oldplane = player->plane_y;
	player->dir_y = player->dir_x * sin(rot) + player->dir_y * cos(rot);
	player->dir_x = player->dir_x * cos(rot) - olddir * sin(rot);
	player->plane_y = player->plane_x * sin(rot) + player->plane_y * cos(rot);
	player->plane_x = player->plane_x * cos(rot) - oldplane * sin(rot);
}

static void	set_move_dir(t_player *player, int key_type, \
										double *move_x_dir, double *move_y_dir)
{
	double	olddir;

	olddir = player->dir_y;
	if (key_type == KEY_A)
	{
		*move_y_dir = (player->dir_x * sin(A_PI) + player->dir_y * cos(A_PI));
		*move_x_dir = (player->dir_x * cos(A_PI) - olddir * sin(A_PI));
		return ;
	}
	else if (key_type == KEY_D)
	{
		*move_y_dir = (player->dir_x * sin(D_PI) + player->dir_y * cos(D_PI));
		*move_x_dir = (player->dir_x * cos(D_PI) - olddir * sin(D_PI));
		return ;
	}
	*move_x_dir = player->dir_x;
	*move_y_dir = player->dir_y;
	return ;
}

static void	move_key(t_game *game, double speed, int key_type)
{
	double		move_y_dir;
	double		move_x_dir;
	t_player	*player;

	player = game->player;
	set_move_dir(player, key_type, &move_x_dir, &move_y_dir);
	if (game->map[(int)(player->pos_y + (move_y_dir * speed) * WALL_DIST)] \
			[(int)(player->pos_x + (move_x_dir * speed) * WALL_DIST)] != '0')
		return ;
	player->pos_y += move_y_dir * speed;
	player->pos_x += move_x_dir * speed;
}

int	key_press(int keycode, t_game *game)
{	
	t_player	*player;

	player = game->player;
	if (keycode == KEY_W)
		move_key(game, 0.1, KEY_W);
	else if (keycode == KEY_S)
		move_key(game, -0.1, KEY_S);
	else if (keycode == KEY_A)
		move_key(game, 0.1, KEY_A);
	else if (keycode == KEY_D)
		move_key(game, 0.1, KEY_D);
	else if (keycode == LEFT_ARROR_KEY)
		rot_view(player, PI / 6);
	else if (keycode == RIGHT_ARROR_KEY)
		rot_view(player, -(PI / 6));
	else if (keycode == KEY_ESC)
		exit(0);
	else
		return (0);
	draw_game_view(game);
	mlx_put_image_to_window(game->mlx, \
									game->mlx_win, game->game_view->img, 0, 0);
	draw_mini_map(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->minimap->img, 0, 0);
	return (0);
}
