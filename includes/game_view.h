/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_view.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:48:32 by kipark            #+#    #+#             */
/*   Updated: 2022/11/16 22:01:27 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_VIEW_H
# define GAME_VIEW_H

# include "struct.h"

# define MINIMAP_RAY_COUNT 100
# define MINIMAP_SIZE 20
# define TEX_WIDTH	64
# define TEX_HEIGHT	64
# define TEX_COUNT 4

void	draw_minimap_player(t_game *game);
void	draw_minimap_ray(t_game *game);
void	set_dda(t_ray_casting *rc, t_player *player, t_game *game, int x);
void	run_dda(t_game *game, t_ray_casting *rc);
void	set_line_length(t_game *game, t_ray_casting *rc, t_player *player);
void	set_draw_texture(t_game *game, t_ray_casting *rc, t_player *player);
void	draw_line(t_ray_casting *rc, t_game *game, int x);
void	draw_game_view(t_game *game);

#endif
