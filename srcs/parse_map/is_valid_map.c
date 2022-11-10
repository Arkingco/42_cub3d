/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:35:06 by jayoon            #+#    #+#             */
/*   Updated: 2022/11/10 20:46:07 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "parse_map.h"

static int	is_zero_or_start_position(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	check_the_door_is_closed(char **map, size_t i, size_t j)
{
	if (map[i - 1][j - 1] == ' ' || map[i - 1][j] == ' ' \
		|| map[i - 1][j + 1] == ' '	|| map[i][j - 1] == ' ' \
		|| map[i][j + 1] == ' ' || map[i + 1][j - 1] == ' ' \
		|| map[i + 1][j] == ' ' || map[i + 1][j + 1] == ' ')
		print_error_str(MSG_ERR_MAP);
}

t_cnt_start_pos	is_valid_map(t_map_info *map_info)
{
	char	**map;
	size_t	i;
	size_t	j;

	map = map_info->map;
	i = 1;
	while (map_info->map_height + 1 > i)
	{
		j = 1;
		while (map_info->map_width + 1 > j)
		{
			if (is_zero_or_start_position(map[i][j]))
				check_the_door_is_closed(map, i, j);
			++j;
		}
		++i;
	}
	return (CUB_ONE);
}
