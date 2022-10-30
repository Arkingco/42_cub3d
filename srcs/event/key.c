/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:53:10 by kipark            #+#    #+#             */
/*   Updated: 2022/10/30 18:28:45 by kipark           ###   ########seoul.kr  */
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
	

	olddir = player->dirY;
	oldplane = player->planeY;
	player->dirY = player->dirX * sin(rot) + player->dirY * cos(rot);
	player->dirX = player->dirX * cos(rot) - olddir * sin(rot);
	player->planeY = player->planeX * sin(rot) + player->planeY * cos(rot);
	player->planeX = player->planeX * cos(rot) - oldplane * sin(rot);
}

static void set_move_dir(t_player *player , int key_type, \
												double *moveX_dir, double *moveY_dir)
{
	double	olddir;

	olddir = player->dirY;
	if (key_type == KEY_A)
	{
		*moveY_dir = (player->dirX * sin(A_PI) + player->dirY * cos(A_PI));
		*moveX_dir = (player->dirX * cos(A_PI) - olddir * sin(A_PI));
		return ;
	}
	else if (key_type == KEY_D)
	{
		*moveY_dir = (player->dirX * sin(D_PI) + player->dirY * cos(D_PI));
		*moveX_dir = (player->dirX * cos(D_PI) - olddir * sin(D_PI));
		return ;
	}
	*moveX_dir = player->dirX;
	*moveY_dir = player->dirY;
	return ;
}

static void move_key(t_game *game, double speed, int key_type)
{
	double		moveY_dir;
	double		moveX_dir;
	t_player	*player;

	player = game->player;
	set_move_dir(player, key_type, &moveX_dir, &moveY_dir);
	if (game->map[(int)(player->posY + (moveY_dir * speed) * 1.2)]\
					[(int)(player->posX + (moveX_dir * speed) * 1.2)] != '0')
						return ;
	player->posY += moveY_dir * speed;
	player->posX += moveX_dir * speed;	
}

int	key_press(int keycode, t_game *game)
{	
	t_player *player;

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
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->game_view->img, 0, 0);
	draw_mini_map(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->minimap->img, 0, 0);
	return (0);
}
