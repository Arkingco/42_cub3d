/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 21:10:42 by jayoon            #+#    #+#             */
/*   Updated: 2022/11/10 16:50:37 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "parse_map.h"

static void	put_in_space_at_edge_and_init(t_map_info *map_info, size_t *p_i, \
				size_t *p_cnt_start_position)
{
	size_t	i;

	*p_i = 1;
	*p_cnt_start_position = 0;
	i = 0;
	map_info->map = ft_safe_malloc(sizeof(char *) * (map_info->map_height + 3));
	while (map_info->map_height + 2 > i)
	{
		map_info->map[i] = ft_safe_malloc(map_info->map_width + 3);
		ft_memset(map_info->map[i], ' ', map_info->map_width + 2);
		++i;
	}
}

static int	is_start_position(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_valid_character(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S' \
		|| c == 'E' || c == 'W');
}

size_t	get_map(t_map_info *map_info, char **temp_map)
{
	size_t	i;
	size_t	j;
	size_t	cnt_start_position;

	put_in_space_at_edge_and_init(map_info, &i, &cnt_start_position);
	while (map_info->map_height + 1 > i)
	{
		j = 1;
		while (temp_map[i - 1][j - 1] != '\0')
		{
			if (temp_map[i - 1][j - 1] != '\n')
				map_info->map[i][j] = temp_map[i - 1][j - 1];
			if (is_start_position(map_info->map[i][j]))
				++cnt_start_position;
			if (cnt_start_position > 1 \
				|| is_valid_character(map_info->map[i][j]) == CUB_FAIL)
				print_error_str(MSG_ERR_MAP);
			++j;
		}
		map_info->map[i][map_info->map_width + 2] = '\0';
		++i;
	}
	map_info->map[map_info->map_height + 2] = NULL;
	return (cnt_start_position);
}
