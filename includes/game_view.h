/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_view.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:48:32 by kipark            #+#    #+#             */
/*   Updated: 2022/11/18 21:00:12 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_VIEW_H
# define GAME_VIEW_H

# include "struct.h"

# define GAME_WIDTH	1500
# define GAME_HEIGHT 1000
# define MINIMAP_RAY_COUNT 100
# define MINIMAP_SIZE 15
# define TEX_WIDTH	64
# define TEX_HEIGHT	64
# define TEX_COUNT 4

void	*my_mlx_xpm_file_to_image(void *xvar, char *file, int *width, \
																int *height);
void	draw_minimap_player(t_game *game);
void	draw_minimap_ray(t_game *game);
void	set_dda(t_ray_casting *rc, t_player *player, t_game *game, int x);
void	run_dda(t_game *game, t_ray_casting *rc);
void	set_line_length(t_game *game, t_ray_casting *rc, t_player *player);
void	set_draw_texture(t_game *game, t_ray_casting *rc, t_player *player);
void	draw_line(t_ray_casting *rc, t_game *game, int x);
void	draw_game_view(t_game *game);

#endif
