/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:47:34 by kipark            #+#    #+#             */
/*   Updated: 2022/10/21 21:08:11 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "game_view.h"
#include "math.h"

#include <stdio.h>
static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_line(t_game *game, int x, double draw_start, double draw_end, int color)
{
	int y;

	y = draw_start;
	while (y < draw_end)
	{
		my_mlx_pixel_put(game->game_view, x, y, color);
		++y;
	}
}

static void draw_background(t_game *game, \
									t_draw_color ceiling, t_draw_color floor)
{
	for (int i=0; i < game->height / 2; ++i)
	{
		for (int j=0 ;j<game->width; ++j)
			my_mlx_pixel_put(game->game_view, j, i, ceiling);
	}
	for (int i=game->height / 2; i < game->height; ++i)
	{
		for (int j=0 ;j<game->width; ++j)
			my_mlx_pixel_put(game->game_view, j, i, floor);
	}
}

void draw_game_view(t_game *game)
{
	t_player *player;
	t_dda dda;

	player = game->player;
	draw_background(game, COLOR_PINK, COLOR_BLACK);
	for(int x = 0; x < game->width; x++)
	{
		double cameraX = 2 * x / (double)game->width - 1;
		double rayDirX = player->dirX + player->planeX * cameraX;
		double rayDirY = player->dirY + player->planeY * cameraX;
		dda.mapX = (int)player->posX;
		dda.mapY = (int)player->posY;
		dda.deltaDistX = fabs(1 / rayDirX);
		dda.deltaDistY = fabs(1 / rayDirY);
		dda.hit = 0;
		if (rayDirX < 0)
		{
			dda.stepX = -1;
			dda.sideDistX = (player->posX - dda.mapX) * dda.deltaDistX;
		}
		else
		{
			dda.stepX = 1;
			dda.sideDistX = (dda.mapX + 1.0 - player->posX) * dda.deltaDistX;
		}
		if (rayDirY < 0)
		{
			dda.stepY = -1;
			dda.sideDistY = (player->posY - dda.mapY) * dda.deltaDistY;
		}
		else
		{
			dda.stepY = 1;
			dda.sideDistY = (dda.mapY + 1.0 - player->posY) * dda.deltaDistY;
		}
		while (dda.hit == 0)
		{
			if (dda.sideDistX < dda.sideDistY)
			{
				dda.sideDistX += dda.deltaDistX;
				dda.mapX += dda.stepX;
				dda.side = 0;
			}
			else
			{
				dda.sideDistY += dda.deltaDistY;
				dda.mapY += dda.stepY;
				dda.side = 1;
			}
			if (game->map[dda.mapY][dda.mapX] > '0') dda.hit = 1;
		}
		if (dda.side == 0)
		 	dda.perpWallDist = (dda.mapX - player->posX + (1 - dda.stepX) / 2) / rayDirX;
		else
			dda.perpWallDist = (dda.mapY - player->posY + (1 - dda.stepY) / 2) / rayDirY;
		dda.lineHeight = (int)(game->height / dda.perpWallDist / 2);
		dda.drawStart = -(dda.lineHeight) / 2 + game->height / 2;
		if (dda.drawStart < 0)
			dda.drawStart = 0;
		dda.drawEnd = dda.lineHeight / 2 + game->height / 2;
		if (dda.drawEnd >= game->height)
			dda.drawEnd = game->height - 1;
		int	color = COLOR_BLACK;
		if (game->map[dda.mapY][dda.mapX] == '1')
			color = COLOR_BLUE;
		else if (game->map[dda.mapY][dda.mapX] == '0')
			continue ;
		if (dda.side == 1) {color = color / 2;}
		draw_line(game, x, dda.drawStart, dda.drawEnd, color);
	}
}
