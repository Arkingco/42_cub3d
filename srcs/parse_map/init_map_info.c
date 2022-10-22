/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:04:54 by jayoon            #+#    #+#             */
/*   Updated: 2022/10/22 20:33:43 by jayoon           ###   ########.fr       */
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

static void	init_texture_path_variable(t_substr_info *info, char **p_str)
{
	info->start = NULL;
	info->end = NULL;
	info->flag = 0;
	*p_str = *p_str + 3;
}

static t_identifier	process_texture_path(t_map_info *map_info, char *str, \
						t_identifier num_iden)
{
	t_substr_info	info;

	init_texture_path_variable(&info, &str);
	while (*str)
	{
		if (*str != ' ')
		{
			if (info.end != NULL)
				print_error_str("Too many information!\n");
			if (info.flag == 0)
			{
				info.start = str;
				info.flag = 1;
			}
			if (*(str + 1) == '\0' || *(str + 1) == ' ')
				info.end = str;
		}
		++str;
	}
	if (info.start != NULL)
		map_info->texture_path[num_iden] \
			= ft_substr(info.start, 0, (info.end - info.start) + 1);
	else
		print_error_str("There is not information!\n");
	return (num_iden);
}

static void	init_color_variable(t_substr_info *info, char **p_str)
{
	info->start = NULL;
	info->end = NULL;
	info->flag = 0;
	*p_str = *p_str + 2;
}

static char	*pass_space(char *str)
{
	while (*str == ' ')
		++str;
	if (*str == '\0')
		return (NULL);
	return (str);
}

static size_t	count_comma(char *str)
{
	size_t	cnt;

	cnt = 0;
	while (*str)
	{
		if (*str == ',')
			++cnt;
		++str;
	}
	return (cnt);
}

static void	check_0_to_255(int num)
{
	if (num < 0 || num > 255)
		print_error_str("Invalid nubmer!\n");
}

static void	get_color(t_map_info *map_info, t_identifier num_iden, char *str)
{
	char			**arr_rgb;
	t_color			color;
	int				num;

	color = RED;
	arr_rgb = ft_split(str, ',');
	while (*arr_rgb)
	{
		num = cub3d_atoi(*arr_rgb);
		if (num == -1)
			print_error_str("Invalid number!\n");
		check_0_to_255(num);
		if (num_iden == FLOOR)
			map_info->floor[color] = num;
		else
			map_info->ceiling[color] = num;
		++color;
		++arr_rgb;
	}
	if (color != 3)
		print_error_str("Invalid information!\n");
}

/*
 * Format is [  "F or C"  R,G,B  ]
 */
static t_identifier	process_color(t_map_info *map_info, char *str, \
						t_identifier num_iden)
{
	t_substr_info	info;
	size_t			cnt_comma;

	init_color_variable(&info, &str);
	str = pass_space(str);
	if (str == NULL)
		return (ELEMENT_FAIL);
	cnt_comma = count_comma(str);
	if (cnt_comma == 2)
		get_color(map_info, num_iden, str);
	else
		print_error_str("Invalid information!\n");
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
	int						i;

	i = 0;
	while (i < 6)
	{
		if (!ft_strncmp(str, arr[i].str, arr[i].len))
			return (arr[i].f_parsing(map_info, str, arr[i].identifier));
		++i;
	}
	return (ELEMENT_FAIL);
}

static void	change_eol_to_nul(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			*str = '\0';
		++str;
	}
}

/*
 * First word followd zero or some space is identifier.
 */
static t_identifier 	parse_string(t_map_info *map_info, char *str)
{
	t_identifier	identifier;

	identifier = ELEMENT_FAIL;
	change_eol_to_nul(str);
	while (*str)
	{
		if (*str != ' ')
			return (check_identifier(map_info, str));
		++str;
	}
	return (identifier);
}

/*
 * If first character is not eol, that identifier will be checked.
 */
static void	init_element(t_map_info *map_info, int fd)
{
	char	*str;
	size_t	cnt_element;	

	cnt_element = 0;
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		if (*str != '\n')
		{
			if (parse_string(map_info, str) == ELEMENT_FAIL)
				print_error_str("Invalid identifier\n");
			++cnt_element;
		}
		free(str);
		str = NULL;
		if (cnt_element > 6)
			break ;
	}
}

void	init_map_info(t_map_info *map_info, int argc, char *file_path)
{
	int			fd;

	if (check_argc(argc))
		print_error_str("Argument must be one\n");
	fd = safe_open(file_path);
	init_element(map_info, fd);
	// init_map_content(map_info, fd);
	close(fd);
}
