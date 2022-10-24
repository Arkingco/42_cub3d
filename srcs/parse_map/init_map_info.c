/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:04:54 by jayoon            #+#    #+#             */
/*   Updated: 2022/10/24 13:24:49 by jayoon           ###   ########.fr       */
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

static int	safe_open(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		exit_perror();
	return (fd);
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
}

static void	check_duplication(t_map_info *map_info)
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
	if (flag_fail == 1)
		print_error_str("Identifier is duplication!\n");
}

void	init_map_info(t_map_info *map_info, int argc, char *file_path)
{
	int			fd;

	if (check_argc(argc))
		print_error_str("Argument must be one\n");
	fd = safe_open(file_path);
	init_map_info_to_initial_value(map_info);
	init_element(map_info, fd);
	check_duplication(map_info);
	// init_map_content(map_info, fd);
	close(fd);
}

	// 중복 없이 모든 식별자를 읽었는지 확인한다.
	// 그렇다면 map_info의 path가 NULL이 아니다.
	// ceiling과 floor의 모든 값이 -1이 아니다.
