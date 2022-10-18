/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:53:10 by kipark            #+#    #+#             */
/*   Updated: 2022/10/18 21:43:50 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "key.h"
#include "cub3d.h"
#include "mlx.h"
#include "minimap.h"
#include <stdlib.h>

#include <stdio.h>
static void move_key(double *posY, double *posX, \
											double move_y, double move_x)
{
	*posY += move_y;
	*posX += move_x;
}

int	key_press(int keycode, t_game *game)
{	
	t_player *player;

	player = game->player;
	if (keycode == KEY_W)
		move_key(&player->posY, &player->posX, - 10.0, 0);
	else if (keycode == KEY_S)
		move_key(&player->posY, &player->posX, 10.0, 0);
	else if (keycode == KEY_A)
		move_key(&player->posY, &player->posX, 0, -10.0);
	else if (keycode == KEY_D)
		move_key(&player->posY, &player->posX, 0, 10.0);
	else if (keycode == KEY_ESC)
		exit(0);
	else
		return (0);
	printf("%f %f\n", player->posY, player->posX);
	draw_mini_map(game);
	// mlx_put_image_to_window(game->mlx, game->mlx_win, game->minimap->img, 0, 0);

	return (0);
}
