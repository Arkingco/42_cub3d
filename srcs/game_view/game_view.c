/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:47:34 by kipark            #+#    #+#             */
/*   Updated: 2022/10/30 18:38:05 by kipark           ###   ########seoul.kr  */
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

int set_view_color(t_game *game, t_ray_casting *rc)
{
	int	color;

	color = 0;
	if (game->map[rc->mapY][rc->mapX] == '1')
		color = COLOR_BLUE;
	if (rc->side == 1)
			color = color / 2;
	return (color);
}

void draw_line(t_game *game, int x, double draw_start, \
											double draw_end, int color)
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

static void set_dda_algorithm(t_ray_casting *rc, t_player *player, \
														t_game *game, int x)
{
	rc->cameraX = 2 * x / (double)game->width - 1;
	rc->rayDirX = player->dirX + player->planeX * rc->cameraX;
	rc->rayDirY = player->dirY + player->planeY * rc->cameraX;
	rc->mapX = (int)player->posX;
	rc->mapY = (int)player->posY;
	rc->deltaDistX = fabs(1 / rc->rayDirX);
	rc->deltaDistY = fabs(1 / rc->rayDirY);
	rc->hit = 0;
	if (rc->rayDirX < 0)
	{
		rc->stepX = -1;
		rc->sideDistX = (player->posX - rc->mapX) * rc->deltaDistX;
	}
	else
	{
		rc->stepX = 1;
		rc->sideDistX = (rc->mapX + 1.0 - player->posX) * rc->deltaDistX;
	}
	if (rc->rayDirY < 0)
	{
		rc->stepY = -1;
		rc->sideDistY = (player->posY - rc->mapY) * rc->deltaDistY;
	}
	else
	{
		rc->stepY = 1;
		rc->sideDistY = (rc->mapY + 1.0 - player->posY) * rc->deltaDistY;
	}
}

static void run_dda_algorithm(t_game *game, t_ray_casting *rc)
{
	while (rc->hit == 0)
	{
		if (rc->sideDistX < rc->sideDistY)
		{
			rc->sideDistX += rc->deltaDistX;
			rc->mapX += rc->stepX;
			rc->side = 0;
		}
		else
		{
			rc->sideDistY += rc->deltaDistY;
			rc->mapY += rc->stepY;
			rc->side = 1;
		}
		if (game->map[rc->mapY][rc->mapX] > '0') rc->hit = 1;
	}
}

static void set_draw_length(t_game *game, t_ray_casting *rc, t_player *player)
{
	if (rc->side == 0)
	{
		rc->perpWallDist = (rc->mapX - player->posX + (1 - rc->stepX) / 2)\
																/ rc->rayDirX;
	}
	else
		rc->perpWallDist = (rc->mapY - player->posY + (1 - rc->stepY) / 2)\
																/ rc->rayDirY;
	rc->lineHeight = (int)(game->height / rc->perpWallDist );
	rc->drawStart = -(rc->lineHeight) / 2 + game->height / 2;
	if (rc->drawStart < 0)
		rc->drawStart = 0;
	rc->drawEnd = rc->lineHeight / 2 + game->height / 2;
	if (rc->drawEnd >= game->height)
		rc->drawEnd = game->height - 1;
}

static int set_texture(t_ray_casting *rc)
{
	if (rc->side == 1)
	{
		if (rc->rayDirY > 0)
			return (2);
		else
			return (3);
	}
	else
	{
		if (rc->rayDirX > 0)
			return (0);
		else
			return (1);
	}
}
void draw_game_view(t_game *game)
{
	t_player		*player;
	t_ray_casting	rc;

	player = game->player;
	draw_background(game, COLOR_PINK, COLOR_BLACK);
	for(int x = 0; x < game->width; x++)
	{
		set_dda_algorithm(&rc, player, game, x);
		run_dda_algorithm(game, &rc);
		set_draw_length(game, &rc, player);

		if (rc.side == 0)
			rc.wallX = player->posY + rc.perpWallDist * rc.rayDirY;
		else
			rc.wallX = player->posX + rc.perpWallDist * rc.rayDirX;
		rc.wallX = rc.wallX - floor((rc.wallX));

		rc.texX = (double)rc.wallX * (double)TEX_WIDTH;
		if(rc.side == 0 && rc.rayDirX > 0) rc.texX = TEX_WIDTH - rc.texX - 1;
		if(rc.side == 1 && rc.rayDirY < 0) rc.texX = TEX_WIDTH - rc.texX - 1;

		rc.step = 1.0 * TEX_HEIGHT / rc.lineHeight;
		rc.texPos = (rc.drawStart - game->height / 2 + rc.lineHeight / 2) * rc.step;
		for(int y = rc.drawStart; y<rc.drawEnd; y++)
		{
			rc.texY = (int)rc.texPos & (TEX_HEIGHT - 1);
			rc.texPos += rc.step;
			
			rc.color = game->texture_color[set_texture(&rc)]\
								[TEX_HEIGHT * rc.texY + (TEX_WIDTH - rc.texX - 1)];
			if(rc.side == 1) rc.color = (rc.color >> 1) & 8355711;
			game->draw_buffer[y][x] = rc.color;
			my_mlx_pixel_put(game->game_view, x, y, game->draw_buffer[y][x]);
		}
	}
}
