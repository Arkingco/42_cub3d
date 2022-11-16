/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:06:09 by kipark            #+#    #+#             */
/*   Updated: 2022/11/16 22:06:12 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"
#include "stdlib.h"
#include "libft.h"
#include "game_view.h"

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static int	get_texture_img(t_ray_casting *rc)
{
	if (rc->side == 1)
	{
		if (rc->raydir_y > 0)
			return (2);
		else
			return (3);
	}
	else
	{
		if (rc->raydir_x > 0)
			return (0);
		else
			return (1);
	}
}

void	set_line_length(t_game *game, t_ray_casting *rc, t_player *player)
{
	if (rc->side == 0)
		rc->perp_wall_dist = (rc->map_x - player->pos_x + (1 - rc->step_x) / 2) \
																/ rc->raydir_x;
	else
		rc->perp_wall_dist = (rc->map_y - player->pos_y + (1 - rc->step_y) / 2) \
																/ rc->raydir_y;
	rc->line_height = (int)(game->height / rc->perp_wall_dist);
	rc->draw_start = -(rc->line_height) / 2 + game->height / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = rc->line_height / 2 + game->height / 2;
	if (rc->draw_end >= game->height)
		rc->draw_end = game->height - 1;
}

void	set_draw_texture(t_game *game, t_ray_casting *rc, t_player *player)
{
	if (rc->side == 0)
	rc->wall_x = player->pos_y + rc->perp_wall_dist * rc->raydir_y;
	else
		rc->wall_x = player->pos_x + rc->perp_wall_dist * rc->raydir_x;
	rc->wall_x = rc->wall_x - floor((rc->wall_x));
	rc->tex_x = (double)rc->wall_x * (double)TEX_WIDTH;
	if (rc->side == 0 && rc->raydir_x > 0)
		rc->tex_x = TEX_WIDTH - rc->tex_x - 1;
	if (rc->side == 1 && rc->raydir_y < 0)
		rc->tex_x = TEX_WIDTH - rc->tex_x - 1;
	rc->step = 1.0 * TEX_HEIGHT / rc->line_height;
	rc->tex_pos = (rc->draw_start - game->height / 2 + rc->line_height / 2) \
																	* rc->step;
}

void	draw_line(t_ray_casting *rc, t_game *game, int x)
{
	int	y;

	y = rc->draw_start;
	while (y < rc->draw_end)
	{
		rc->tex_y = (int)rc->tex_pos & (TEX_HEIGHT - 1);
		rc->tex_pos += rc->step;
		rc->color = game->texture_color[get_texture_img(rc)] \
						[TEX_HEIGHT * rc->tex_y + (TEX_WIDTH - rc->tex_x - 1)];
		if (rc->side == 1)
			rc->color = (rc->color >> 1) & 8355711;
		my_mlx_pixel_put(game->game_view, x, y, rc->color);
		++y;
	}
}
