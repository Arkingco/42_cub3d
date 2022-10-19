/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:04:54 by jayoon            #+#    #+#             */
/*   Updated: 2022/10/19 21:58:26 by jayoon           ###   ########.fr       */
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

static t_num_iden	process_texture_path(t_map_info *map_info, char *str, \
						t_num_iden num_iden)
{
	// 실패하면 ELEMENT_FAIL
	char	*start;
	char	*end;
	int		flag;

	start = NULL;
	end = NULL;
	str = str + 3;
	flag = 0;
	while (*str)
	{
		if (*str != ' ')
		{
			if (end != NULL)
				return (ELEMENT_FAIL);
			if (flag == 0)
				start = str;
			flag = 1;
			if (*(str + 1) == '\0' || *(str + 1) == ' ')
				end = str;
		}
		++str;
	}
	if (str != NULL)
		// map_info->texture_path[num_iden] = ft_substr();
	return (num_iden);
}

static t_num_iden	process_color(t_map_info *map_info, char *str, \
						t_num_iden num_iden)
{
	// 실패하면 ELEMENT_FAIL
	return (num_iden);
}

static t_num_iden	what_is_identifier(t_map_info *map_info, char *str)
{
	const t_identifier	arr[6] = {{"EA ", 3, EAST, process_texture_path}, \
									{"WE ", 3, WEST, process_texture_path}, \
									{"SO ", 3, SOUTH, process_texture_path}, \
									{"NO ", 3, NORTH, process_texture_path}, \
									{"F ", 2, FLOOR, process_color}, \
									{"C ", 2, CEILING, process_color}};
	int					i;

	i = 0;
	while (i < 6)
	{
		if (!ft_strncmp(str, arr[i].str, arr[i].len))
			return (arr[i].f_parsing(map_info, str, arr[i].identifier));
		++i;
	}
	return (ELEMENT_FAIL);
}

static t_num_iden 	parse_element(t_map_info *map_info, char *str)
{
	while (*str)
	{
		if (*str != ' ')
			return (what_is_identifier(map_info, str));
		++str;
	}
	return (ELEMENT_FAIL);
}

static void	init_element(t_map_info *map_info, int fd)
{
	char		*str;

	// texture 4개, color 2개, 이어져 있는 map 1개 총 7개이후 있는 요소는 에러
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		if (*str != '\n')
		{
			if (parse_element(map_info, str) == ELEMENT_FAIL)
				print_error_str("Invalid identifier\n");
		}
		free(str);
		str = NULL;
	}
}

void	init_map_info(t_map_info *map_info, int argc, char *file_path)
{
	int			fd;

	if (check_argc(argc))
		print_error_str("Argument must be one\n");
	fd = safe_open(file_path);
	// element 값 데이터 가공
	init_element(map_info, fd);
	// map content 데이터 가공
	close(fd);
}
