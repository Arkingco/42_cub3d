/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_start_pos_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:41:02 by jayoon            #+#    #+#             */
/*   Updated: 2022/11/18 14:48:27 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_map.h"

static void	get_view_direction(char c, t_map_info *map_info)
{
	if (c == 'E')
		map_info->view_direction = E;
	else if (c == 'W')
		map_info->view_direction = W;
	else if (c == 'S')
		map_info->view_direction = S;
	else
		map_info->view_direction = N;
}

static void	get_start_position(t_map_info *map_info, size_t i, size_t j)
{
	map_info->start_pos_x = (double)j;
	map_info->start_pos_y = (double)i;
}

void	get_start_pos_info(char c, t_map_info *map_info, \
				size_t i, size_t j)
{
	get_view_direction(c, map_info);
	get_start_position(map_info, i, j);
}
