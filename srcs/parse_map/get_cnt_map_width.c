/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cnt_map_width.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:50:25 by jayoon            #+#    #+#             */
/*   Updated: 2022/11/18 18:26:24 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include <stdlib.h>
#include "parse_map.h"

size_t	get_cnt_map_width(char **map)
{
	size_t	i;
	size_t	j;
	size_t	cnt_width;
	size_t	max;

	i = 0;
	max = 0;
	while (map[i])
	{
		cnt_width = 0;
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '\n')
				++cnt_width;
			++j;
		}
		if (max < cnt_width)
			max = cnt_width;
		++i;
	}
	if (max > MAP_LIMIT_WIDTH)
		print_error_str(MSG_ERR_MAP_IS_BIG);
	return (max);
}
