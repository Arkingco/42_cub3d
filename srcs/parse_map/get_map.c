/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 21:10:42 by jayoon            #+#    #+#             */
/*   Updated: 2022/11/15 22:40:43 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "parse_map.h"

static void	put_in_space_at_edge_and_init(t_map_info *map_info, size_t *p_i, \
				size_t *p_cnt_start_pos, size_t *p_cnt_valid_c)
{
	size_t	i;

	*p_i = 1;
	*p_cnt_start_pos = 0;
	*p_cnt_valid_c = 0;
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

static int	is_start_position(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_valid_character(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S' \
		|| c == 'E' || c == 'W');
}

static int	is_not_space_or_eol(char c)
{
	return (c != ' ' && c != '\n');
}

size_t	get_map(t_map_info *map_info, char **temp_map)
{
	size_t	i;
	size_t	j;
	size_t	cnt_start_pos;
	size_t	cnt_valid_c;

	put_in_space_at_edge_and_init(map_info, &i, &cnt_start_pos, &cnt_valid_c);
	while (map_info->map_height + 1 > i)
	{
		j = 1;
		while (temp_map[i - 1][j - 1] != '\0')
		{
			if (temp_map[i - 1][j - 1] != '\n')
				map_info->map[i][j] = temp_map[i - 1][j - 1];
			if (is_not_space_or_eol(map_info->map[i][j]))
				++cnt_valid_c;
			if (is_start_position(map_info->map[i][j]))
				++cnt_start_pos;
			if (is_valid_character(map_info->map[i][j]) == CUB_FAIL)
				print_error_str(MSG_ERR_MAP);
			++j;
		}
		if (cnt_start_pos > 1 || cnt_valid_c == 0)
			print_error_str(MSG_ERR_MAP);
		++i;
	}
	return (cnt_start_pos);
}
