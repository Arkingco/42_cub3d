/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 21:22:01 by jayoon            #+#    #+#             */
/*   Updated: 2022/11/05 03:50:23 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "parse_map.h"

static char	**init_temp_map(t_map_info *map_info, int this_fd)
{
	char	**temp_map;
	char	*str;
	size_t	i;

	i = 0;
	temp_map = ft_safe_malloc(sizeof(char *) * (map_info->map_height + 1));
	str = pass_empty_line(this_fd);
	while (1)
	{
		temp_map[i] = str;
		++i;
		if (map_info->map_height == i)
			break ;
		str = get_next_line(this_fd);
	}
	temp_map[map_info->map_height] = NULL;
	return (temp_map);
}

/**
 * feat: check the number of characters and whether valid character
 */
static int	check_valid_character(char c)
{
	if (c == '1')
	{

	}
}

static void	put_in_space_at_edge_and_init(t_map_info *map_info)
{
	size_t	i;

	i = 0;
	map_info->map = ft_safe_malloc(sizeof(char *) * (map_info->map_height + 3));
	while (map_info->map_height + 2 > i)
	{
		map_info->map[i] = ft_safe_malloc(map_info->map_width + 3);
		ft_memset(map_info->map[i], ' ', map_info->map_width + 2);
		++i;
	}
}

static void	get_map(t_map_info *map_info, char **temp_map)
{
	size_t	i;
	size_t	j;

	put_in_space_at_edge_and_init(map_info);
	i = 1;
	while (map_info->map_height + 1 > i)
	{
		j = 1;
		while (temp_map[i - 1][j - 1] != '\0')
		{
			if (temp_map[i - 1][j - 1] != '\n')
				map_info->map[i][j] = temp_map[i - 1][j - 1];
			if (check_valid_character(map_info->map[i][j]))
				print_error_str(MSG_ERR_MAP);
			++j;
		}
		map_info->map[i][map_info->map_width + 2] = '\0';
		++i;
	}
	map_info->map[map_info->map_height + 2] = NULL;
}

#include <stdio.h>
void	init_map_content(t_map_info *map_info, int this_fd, \
				char *file_path, size_t cnt_gnl)
{
	char	*str;
	char	**temp_map;
	int		temp_fd;

	temp_fd = safe_open(file_path);
	pass_element(cnt_gnl, temp_fd);
	str = pass_empty_line(temp_fd);
	if (str == NULL)
		print_error_str(MSG_ERR_MAP);
	ft_safe_free(str);
	map_info->map_height = get_cnt_map_height(temp_fd);
	str = pass_empty_line(temp_fd);
	close(temp_fd);
	if (str != NULL)
		print_error_str(MSG_ERR_MAP);
	temp_map = init_temp_map(map_info, this_fd);
	close(this_fd);
	map_info->map_width = get_cnt_map_width(temp_map);
	get_map(map_info, temp_map);
	ft_safe_free_two_dimentions_arr(temp_map);

	//test
	size_t	i = 0;
	size_t	j = 0;
	while (map_info->map[i])
	{
		j = 0;
		while (map_info->map[i][j])
		{
			write(1, &map_info->map[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}
