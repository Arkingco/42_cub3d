/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:04:54 by jayoon            #+#    #+#             */
/*   Updated: 2022/10/20 21:39:55 by jayoon           ###   ########.fr       */
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

static void	init_variable(t_substr_info *info, char **str, int *flag)
{
	info->start = NULL;
	info->end = NULL;
	*str = *str + 3;
	*flag = 0;
}

static t_identifier	process_texture_path(t_map_info *map_info, char *str, \
						t_identifier num_iden)
{
	t_substr_info	info;
	int				flag;

	init_variable(&info, &str, &flag);
	while (*str != '\n')
	{
		if (*str != ' ')
		{
			if (info.end != NULL)
				print_error_str("Too many information!\n");
			if (flag == 0)
				info.start = str;
			flag = 1;
			if (*(str + 1) == '\n' || *(str + 1) == ' ')
				info.end = str;
		}
		++str;
	}
	if (info.start != NULL)
		// map_info->texture_path[num_iden] = ft_substr();
	else
		print_error_str("There is not information!\n");
	return (num_iden);
}

static t_identifier	process_color(t_map_info *map_info, char *str, \
						t_identifier num_iden)
{
	// 실패하면 ELEMENT_FAIL
	return (num_iden);
}

static t_identifier	check_identifier(t_map_info *map_info, char *str)
{
	const t_identifier_info	arr[6] = {{"EA ", 3, EAST, process_texture_path}, \
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

/**
 * First character followd some space is identifier.
 */
static t_identifier 	parse_string(t_map_info *map_info, char *str)
{
	while (*str != '\n')
	{
		if (*str != ' ')
			return (check_identifier(map_info, str));
		++str;
	}
	return (ELEMENT_FAIL);
}

static void	init_element(t_map_info *map_info, int fd)
{
	char		*str;

	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		if (*str != '\n')
		{
			if (parse_string(map_info, str) == ELEMENT_FAIL)
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
	init_element(map_info, fd);
	// map content 데이터 가공
	close(fd);
}
