/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:53:10 by kipark            #+#    #+#             */
/*   Updated: 2022/10/14 16:02:20 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "key.h"
#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>


#include <stdio.h>
static void move_key(float *player_y_point, float *player_x_point, \
											float move_y, float move_x)
{
	*player_y_point += move_y;
	*player_x_point += move_x;
}

static void draw_mini_map(t_param *param)
{
	printf("in here2 %f %f\n", param->mini_map->player_y, param->mini_map->player_x);

	mlx_put_image_to_window(param->mlx, param->mlx_win, \
									param->mini_map->map.img, 0, 0);
	mlx_put_image_to_window(param->mlx, param->mlx_win, \
							param->mini_map->player.img, \
							param->mini_map->player_x, \
							param->mini_map->player_y);
}

int	key_press(int keycode, t_param *param)
{	
	t_mini_map *this_mini_map;

	this_mini_map = param->mini_map;
	if (keycode == KEY_W)
		move_key(&this_mini_map->player_y, &this_mini_map->player_x, -10.0, 0);
	else if (keycode == KEY_S)
		move_key(&this_mini_map->player_y, &this_mini_map->player_x, 10.0, 0);
	else if (keycode == KEY_A)
		move_key(&this_mini_map->player_y, &this_mini_map->player_x, 0, -10.0);
	else if (keycode == KEY_D)
		move_key(&this_mini_map->player_y, &this_mini_map->player_x, 0, 10.0);
	else if (keycode == KEY_ESC)
		exit(0);
	else
		return (0);
	printf("in here %f %f\n", this_mini_map->player_y, this_mini_map->player_x);
	draw_mini_map(param);
	return (0);
}
