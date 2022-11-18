/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:57:19 by kipark            #+#    #+#             */
/*   Updated: 2022/11/18 16:48:33 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "struct.h"
# include "minimap.h"
# include "parse_map.h"

# define EXIT_ERROR_PLAG		1
# define WRITE_ERROR_FD			2

void	set_background(void *mlx, void *mlx_win);
void	set_player(t_game *game, t_map_info *map_info);
void	set_game(t_game *game, t_map_info *map_info);
void	set_texture(t_game *game);

#endif
