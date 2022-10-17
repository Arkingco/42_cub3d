/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:41:09 by kipark            #+#    #+#             */
/*   Updated: 2022/10/17 13:59:54 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# define PI 3.141592

# include "struct.h"
typedef struct s_mini_map
{
	t_data	map;
	t_data	player;
	t_data	ray;
	float	player_y;
	float	player_x;
	float	player_ray_line;
}	t_mini_map;

void	set_mini_map(t_mini_map *mini_map, char **map);
void	set_mini_map_player(t_mini_map *player);

#endif
