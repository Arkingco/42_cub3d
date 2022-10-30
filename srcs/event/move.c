/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 14:20:55 by kipark            #+#    #+#             */
/*   Updated: 2022/10/30 14:24:05 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "key.h"
#include "cub3d.h"
#include "mlx.h"
#include <math.h>
#include "minimap.h"
#include "game_view.h"
#include <stdlib.h>

#include <stdio.h>
void move_forward(t_game *game, double speed)
{
	double		move_X;
	double		move_Y;
	t_player	*player;

	player = game->player;
	move_X = player->dirX * speed;
	move_Y = player->dirY * speed;

	printf("%d %d\n", (int)(player->posX + move_X), (int)(player->posY + move_Y));
	printf("pos x: %f pos y:%f \n",player->posX, player->posY);
	if (game->map[(int)(player->posY + move_Y * 1.2)]\
					[(int)(player->posX + move_X * 1.2)] != '0')
						return ;
	player->posX += move_X;	
	player->posY += move_Y;
}

void move_back(t_game *game, double speed)
{
	double		move_X;
	double		move_Y;
	t_player	*player;

	player = game->player;
	move_X = player->dirX * speed;
	move_Y = player->dirY * speed;

	printf("%d %d\n", (int)(player->posX + move_X), (int)(player->posY + move_Y));
	printf("pos x: %f pos y:%f \n",player->posX, player->posY);
	if (game->map[(int)(player->posY + move_Y * 1.2)]\
					[(int)(player->posX + move_X * 1.2)] != '0')
						return ;
	player->posX += move_X;	
	player->posY += move_Y;
}

void move_left(t_game *game, double speed)
{
	double		move_X;
	double		move_Y;
	t_player	*player;

	player = game->player;
	move_X = player->dirX * speed;
	move_Y = player->dirY * speed;

	printf("%d %d\n", (int)(player->posX + move_X), (int)(player->posY + move_Y));
	printf("pos x: %f pos y:%f \n",player->posX, player->posY);
	if (game->map[(int)(player->posY + move_Y * 1.2)]\
					[(int)(player->posX + move_X * 1.2)] != '0')
						return ;
	player->posX += move_X;	
	player->posY += move_Y;
}

void move_right(t_game *game, double speed)
{
	double		move_X;
	double		move_Y;
	t_player	*player;

	player = game->player;
	move_X = player->dirX * speed;
	move_Y = player->dirY * speed;

	printf("%d %d\n", (int)(player->posX + move_X), (int)(player->posY + move_Y));
	printf("pos x: %f pos y:%f \n",player->posX, player->posY);
	if (game->map[(int)(player->posY + move_Y * 1.2)]\
					[(int)(player->posX + move_X * 1.2)] != '0')
						return ;
	player->posX += move_X;	
	player->posY += move_Y;
}
