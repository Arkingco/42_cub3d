/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 21:10:42 by jayoon            #+#    #+#             */
/*   Updated: 2022/11/18 14:45:08 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "parse_map.h"

static void	put_in_space_at_edge_and_init(t_map_info *map_info, size_t *p_i, \
				t_get_map_cnt *cnt)
{
	size_t	i;

	map_info->view_direction = 0;
	map_info->start_pos_x = 0;
	map_info->start_pos_y = 0;
	*p_i = 1;
	cnt->cnt_start_pos = 0;
	cnt->cnt_valid_c = 0;
	i = 0;
	map_info->map = ft_safe_malloc(sizeof(char *) * (map_info->map_height + 3));
	while (map_info->map_height + 2 > i)
	{
		map_info->map[i] = ft_safe_malloc(map_info->map_width + 3);
		ft_memset(map_info->map[i], ' ', map_info->map_width + 2);
		map_info->map[i][map_info->map_width + 2] = '\0';
		++i;
	}
	map_info->map[map_info->map_height + 2] = NULL;
}

static void	init_j_and_cnt_valid_c(size_t *p_j, size_t *p_cnt_valid_c)
{
	*p_j = 1;
	*p_cnt_valid_c = 0;
}

size_t	get_map(t_map_info *map_info, char **temp_map)
{
	size_t			i;
	size_t			j;
	t_get_map_cnt	cnt;

	put_in_space_at_edge_and_init(map_info, &i, &cnt);
	while (map_info->map_height + 1 > i)
	{
		init_j_and_cnt_valid_c(&j, &cnt.cnt_valid_c);
		while (temp_map[i - 1][j - 1] != '\0')
		{
			if (temp_map[i - 1][j - 1] != '\n')
				map_info->map[i][j] = temp_map[i - 1][j - 1];
			get_cnt(map_info->map[i][j], &cnt);
			if (is_valid_character(map_info->map[i][j]) == CUB_FAIL)
				print_error_str(MSG_ERR_MAP);
			if (is_start_position(map_info->map[i][j]))
				get_start_pos_info(map_info->map[i][j], map_info, i, j);
			++j;
		}
		if (cnt.cnt_start_pos > 1 || cnt.cnt_valid_c == 0)
			print_error_str(MSG_ERR_MAP);
		++i;
	}
	return (cnt.cnt_start_pos);
}
