/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:04:54 by jayoon            #+#    #+#             */
/*   Updated: 2022/11/10 20:20:19 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "error.h"
#include <fcntl.h>
#include "libft.h"
#include "parse_map.h"
#include <stdio.h>
#include <unistd.h>

static int	check_argc(int argc)
{
	return (argc != 2);
}

static void	init_map_info_to_initial_value(t_map_info *map_info)
{
	size_t	i;

	i = 0;
	while (i < CNT_TEXTURE)
	{
		map_info->texture_path[i] = NULL;
		if (i < CNT_COLOR)
		{
			map_info->ceiling[i] = -1;
			map_info->floor[i] = -1;
		}
		++i;
	}
	map_info->map_width = 0;
	map_info->map_height = 0;
}

static int	check_element_parsing(t_map_info *map_info)
{
	size_t	i;
	int		flag_fail;

	i = 0;
	flag_fail = 0;
	while (i < CNT_TEXTURE)
	{
		if (map_info->texture_path[i] == NULL)
			flag_fail = 1;
		if (i < CNT_COLOR)
		{
			if (map_info->ceiling[i] == -1 || map_info->floor[i] == -1)
				flag_fail = 1;
		}
		++i;
	}
	return (flag_fail);
}

static int	check_map_name_format(char *file_path)
{
	char	*this_str;

	this_str = ft_strrchr(file_path, '.');
	if (this_str == NULL)
		return (1);
	if (ft_strncmp(this_str, ".cub", 5))
		return (1);
	return (0);
}

static int	is_zero_or_start_position(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	check_the_door_is_closed(char **map, size_t i, size_t j)
{
	if (map[i - 1][j - 1] == ' ' || map[i - 1][j] == ' ' \
		|| map[i - 1][j + 1] == ' '	|| map[i][j - 1] == ' ' \
		|| map[i][j + 1] == ' '|| map[i + 1][j - 1] == ' ' \
		|| map[i + 1][j] == ' '|| map[i + 1][j + 1] == ' ')
		print_error_str(MSG_ERR_MAP);
}

static t_cnt_start_position	is_valid_map(t_map_info *map_info)
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

//test
#include <stdio.h>
static void	print_map(t_map_info *map_info)
{
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

void	init_map_info(t_map_info *map_info, int argc, char *file_path)
{
	size_t	cnt_gnl;
	int		fd;

	if (check_argc(argc))
		print_error_str(MSG_ERR_ARGS);
	if (check_map_name_format(file_path))
		print_error_str(MSG_ERR_FILE_NAME);
	fd = safe_open(file_path);
	init_map_info_to_initial_value(map_info);
	cnt_gnl = init_element(map_info, fd);
	if (check_element_parsing(map_info))
		print_error_str(MSG_ERR_ELEMENT);
	init_map_content(map_info, fd, file_path, cnt_gnl);
	if (is_valid_map(map_info) == CUB_ZERO)
		print_error_str(MSG_ERR_MAP);

	//test
	print_map(map_info);
}
