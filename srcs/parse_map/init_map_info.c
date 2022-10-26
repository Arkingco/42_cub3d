/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:04:54 by jayoon            #+#    #+#             */
/*   Updated: 2022/10/26 18:01:42 by jayoon           ###   ########.fr       */
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
	while (i < 4)
	{
		map_info->texture_path[i] = NULL;
		if (i < 3)
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
	while (i < 4)
	{
		if (map_info->texture_path[i] == NULL)
			flag_fail = 1;
		if (i < 3)
		{
			if (map_info->ceiling[i] == -1 || map_info->floor[i] == -1)
				flag_fail = 1;
		}
		++i;
	}
	return (flag_fail);
}

void	init_map_info(t_map_info *map_info, int argc, char *file_path)
{
	size_t	cnt_gnl;
	int		fd;

	if (check_argc(argc))
		print_error_str("Argument must be one\n");
	fd = safe_open(file_path);
	init_map_info_to_initial_value(map_info);
	cnt_gnl = init_element(map_info, fd);
	if (check_element_parsing(map_info))
		print_error_str("There are not enough elements!\n");
	init_map_content(map_info, fd, file_path, cnt_gnl);
}
