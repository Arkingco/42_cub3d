/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:53:10 by kipark            #+#    #+#             */
/*   Updated: 2022/10/19 21:08:23 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "key.h"
#include "cub3d.h"
#include "mlx.h"
#include <math.h>
#include "minimap.h"
#include <stdlib.h>

#include <stdio.h>
static void	rot_view(t_player *player, double rot_speed)
{
	double	olddir;
	double	oldplane;
	

	olddir = player->dirY;
	oldplane = player->planeY;
	player->dirY = player->dirX * sin(rot_speed) + player->dirY * cos(rot_speed);
	player->dirX = player->dirX * cos(rot_speed) - olddir * sin(rot_speed);
	player->planeY = player->planeX * sin(rot_speed) + player->planeY * cos(rot_speed);
	player->planeX = player->planeX * cos(rot_speed) - oldplane * sin(rot_speed);
	printf("pos x: %f pos y:%f \n",player->posX, player->posY);
	printf("dirX : %f   dirY : %f	planeX : %f	planeY : %f\n", player->dirX, player->dirY, player->planeX, player->planeY);
}

static void move_key(t_player *player, double move_x, \
										double move_y)
{
	double	move_pos_X;
	double	move_pos_Y;

	move_pos_X = player->dirX * move_x;
	move_pos_Y = player->dirY * move_y;
	player->posX += move_pos_X;	
	player->posY += move_pos_Y;
}

int	key_press(int keycode, t_game *game)
{	
	t_player *player;

	player = game->player;
	if (keycode == KEY_W)
		move_key(player, 10.0, 10.0);
	else if (keycode == KEY_S)
		move_key(player, -10.0, -10.0);
	else if (keycode == KEY_A)
		move_key(player, 0, 10);
	else if (keycode == KEY_D)
		move_key(player, 0, -10);
	else if (keycode == LEFT_ARROR_KEY)
		rot_view(player, PI / 6);
	else if (keycode == RIGHT_ARROR_KEY)
		rot_view(player, -(PI / 6));
	else if (keycode == KEY_ESC)
		exit(0);
	else
		return (0);
	draw_mini_map(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->minimap->img, 0, 0);

	return (0);
}
