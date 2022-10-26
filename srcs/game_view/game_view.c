/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:47:34 by kipark            #+#    #+#             */
/*   Updated: 2022/10/26 16:25:47 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"
#include "stdlib.h"
#include "libft.h"
#include "game_view.h"

#include <stdio.h>
static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int set_view_color(t_game *game, t_dda *dda)
{
	int	color;

	color = 0;
	if (game->map[dda->mapY][dda->mapX] == '1')
		color = COLOR_BLUE;
	if (dda->side == 1)
			color = color / 2;
	return (color);
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

static void set_dda_algorithm(t_dda *dda, t_player *player, t_game *game, int x)
{
	dda->cameraX = 2 * x / (double)game->width - 1;
	dda->rayDirX = player->dirX + player->planeX * dda->cameraX;
	dda->rayDirY = player->dirY + player->planeY * dda->cameraX;
	dda->mapX = (int)player->posX;
	dda->mapY = (int)player->posY;
	dda->deltaDistX = fabs(1 / dda->rayDirX);
	dda->deltaDistY = fabs(1 / dda->rayDirY);
	printf("%f %f \n", dda->deltaDistX, dda->deltaDistY);
	dda->hit = 0;
	if (dda->rayDirX < 0)
	{
		dda->stepX = -1;
		dda->sideDistX = (player->posX - dda->mapX) * dda->deltaDistX;
	}
	else
	{
		dda->stepX = 1;
		dda->sideDistX = (dda->mapX + 1.0 - player->posX) * dda->deltaDistX;
	}
	if (dda->rayDirY < 0)
	{
		dda->stepY = -1;
		dda->sideDistY = (player->posY - dda->mapY) * dda->deltaDistY;
	}
	else
	{
		dda->stepY = 1;
		dda->sideDistY = (dda->mapY + 1.0 - player->posY) * dda->deltaDistY;
	}
}

static void run_dda_algorithm(t_game *game, t_dda *dda)
{
	while (dda->hit == 0)
	{
		if (dda->sideDistX < dda->sideDistY)
		{
			dda->sideDistX += dda->deltaDistX;
			dda->mapX += dda->stepX;
			dda->side = 0;
		}
		else
		{
			dda->sideDistY += dda->deltaDistY;
			dda->mapY += dda->stepY;
			dda->side = 1;
		}
		if (game->map[dda->mapY][dda->mapX] > '0') dda->hit = 1;
	}
}

static void set_draw_length(t_game *game, t_dda *dda, t_player *player)
{
	if (dda->side == 0)
		 	dda->perpWallDist = (dda->mapX - player->posX + (1 - dda->stepX) / 2) / dda->rayDirX;
	else
		dda->perpWallDist = (dda->mapY - player->posY + (1 - dda->stepY) / 2) / dda->rayDirY;
	dda->lineHeight = (int)(game->height / dda->perpWallDist );
	dda->drawStart = -(dda->lineHeight) / 2 + game->height / 2;
	if (dda->drawStart < 0)
		dda->drawStart = 0;
	dda->drawEnd = dda->lineHeight / 2 + game->height / 2;
	if (dda->drawEnd >= game->height)
		dda->drawEnd = game->height - 1;
}

void draw_game_view(t_game *game)
{
	t_player *player;
	t_dda dda;

	player = game->player;

	draw_background(game, COLOR_PINK, COLOR_BLACK);
	for(int x = 0; x < game->width; x++)
	{
		set_dda_algorithm(&dda, player, game, x);
		run_dda_algorithm(game, &dda);
		set_draw_length(game, &dda, player);

		//texturing calculations
		int texNum = game->map[dda.mapY][dda.mapX] - '1'; //1 subtracted from it so that texture 0 can be used!

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (dda.side == 0) wallX = player->posY + dda.perpWallDist * dda.rayDirY;
		else				wallX = player->posX + dda.perpWallDist * dda.rayDirX;
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = (int)wallX * (double)TEX_WIDTH;
		if(dda.side == 0 && dda.rayDirX > 0) texX = TEX_WIDTH - texX - 1;
		if(dda.side == 1 && dda.rayDirY < 0) texX = TEX_WIDTH - texX - 1;

		double step = 1.0 * TEX_HEIGHT / dda.lineHeight;
      // Starting texture coordinate
		double texPos = (dda.drawStart - game->height / 2 + dda.lineHeight / 2) * step;
		for(int y = dda.drawStart; y<dda.drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (TEX_HEIGHT - 1);
			texPos += step;
			dda.color = game->texture_color[texNum][TEX_HEIGHT * texY + texX];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if(dda.side == 1) dda.color = (dda.color >> 1) & 8355711;
			game->draw_buffer[y][x] = dda.color;
			my_mlx_pixel_put(game->game_view, x, y, game->draw_buffer[y][x]);
		}
	}
}
