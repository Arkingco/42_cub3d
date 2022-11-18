/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 20:07:24 by kipark            #+#    #+#             */
/*   Updated: 2022/11/18 21:15:31 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "game_view.h"
#include "cub3d.h"
#include "mlx.h"
#include "libft.h"

static unsigned int	my_mlx_pixel_catch(t_data *data, int x, int y)
{
	return (*(unsigned int *)(data->addr + \
					y * data->line_length + x * (data->bits_per_pixel / 8)));
}

static void	set_img_addr(t_texture *texture)
{
	texture->east_img->addr = mlx_get_data_addr(texture->east, \
	&texture->east_img->bits_per_pixel, \
	&texture->east_img->line_length, &texture->east_img->endian);
	texture->west_img->addr = mlx_get_data_addr(texture->west, \
	&texture->west_img->bits_per_pixel, \
	&texture->west_img->line_length, &texture->west_img->endian);
	texture->south_img->addr = mlx_get_data_addr(texture->south, \
	&texture->south_img->bits_per_pixel, \
	&texture->south_img->line_length, &texture->south_img->endian);
	texture->north_img->addr = mlx_get_data_addr(texture->north, \
	&texture->north_img->bits_per_pixel, \
	&texture->north_img->line_length, &texture->north_img->endian);
}

static void	set_texture_pixel(t_game *game, t_texture *tex)
{
	int	i;
	int	y;
	int	x;

	game->texture_color = ft_safe_malloc(sizeof(int *) * TEX_COUNT);
	i = -1;
	while (++i < TEX_COUNT)
		game->texture_color[i] = \
						ft_safe_malloc(sizeof(int) * (TEX_HEIGHT * TEX_WIDTH));
	y = -1;
	while (++y < TEX_HEIGHT)
	{
		x = -1;
		while (++x < TEX_WIDTH)
		{
			game->texture_color[0][TEX_WIDTH * y + x] = \
									my_mlx_pixel_catch(tex->east_img, x, y);
			game->texture_color[1][TEX_WIDTH * y + x] = \
									my_mlx_pixel_catch(tex->west_img, x, y);
			game->texture_color[2][TEX_WIDTH * y + x] = \
									my_mlx_pixel_catch(tex->south_img, x, y);
			game->texture_color[3][TEX_WIDTH * y + x] = \
									my_mlx_pixel_catch(tex->north_img, x, y);
		}
	}
}

void	set_texture(t_game *game, t_map_info *map_info)
{
	int			img_witdh;
	int			img_height;
	t_texture	*tex;

	tex = game->texture;
	tex->east = my_mlx_xpm_file_to_image(game->mlx, \
							map_info->texture_path[0], &img_witdh, &img_height);
	tex->west = my_mlx_xpm_file_to_image(game->mlx, \
							map_info->texture_path[1], &img_witdh, &img_height);
	tex->south = my_mlx_xpm_file_to_image(game->mlx, \
							map_info->texture_path[2], &img_witdh, &img_height);
	tex->north = my_mlx_xpm_file_to_image(game->mlx, \
							map_info->texture_path[3], &img_witdh, &img_height);
	tex->east_img = ft_safe_malloc(sizeof(t_data));
	tex->west_img = ft_safe_malloc(sizeof(t_data));
	tex->south_img = ft_safe_malloc(sizeof(t_data));
	tex->north_img = ft_safe_malloc(sizeof(t_data));
	set_img_addr(tex);
	set_texture_pixel(game, tex);
}
