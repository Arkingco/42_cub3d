/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:47:34 by kipark            #+#    #+#             */
/*   Updated: 2022/11/18 21:07:52 by kipark           ###   ########seoul.kr  */
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

static void	draw_background(t_game *game, \
									t_draw_color ceiling, t_draw_color floor)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->height / 2)
	{
		j = -1;
		while (++j < game->width)
			my_mlx_pixel_put(game->game_view, j, i, ceiling);
	}
	i = game->height / 2 - 1;
	while (++i < game->height)
	{
		j = -1;
		while (++j < game->width)
			my_mlx_pixel_put(game->game_view, j, i, floor);
	}
}

void	draw_game_view(t_game *game)
{
	t_player		*player;
	t_ray_casting	rc;
	int				x;

	draw_background(game, game->ceiling_info, game->floor_info);
	player = game->player;
	x = 0;
	while (x < game->width)
	{
		set_dda(&rc, player, game, x);
		run_dda(game, &rc);
		set_line_length(game, &rc, player);
		set_draw_texture(game, &rc, player);
		draw_line(&rc, game, x);
		++x;
	}
}
