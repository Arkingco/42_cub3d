/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cnt_map_width.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:50:25 by jayoon            #+#    #+#             */
/*   Updated: 2022/10/26 11:44:32 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

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
	return (max);
}
