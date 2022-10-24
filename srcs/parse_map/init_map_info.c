/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:04:54 by jayoon            #+#    #+#             */
/*   Updated: 2022/10/24 16:51:11 by jayoon           ###   ########.fr       */
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

static void	pass_element(size_t cnt_gnl, int temp_fd)
{
	size_t	i;
	char	*str;

	i = 0;
	str = NULL;
	while (cnt_gnl > i)
	{
		str = get_next_line(temp_fd);
		free(str);
		str = NULL;
		++i;
	}
}

static t_gnl_flag	pass_empty_line(int	temp_fd)
{
	char		*str;
	t_gnl_flag	flag;	

	while (1)
	{
		str = get_next_line(temp_fd);
		if (str == NULL || *str != '\n')
		{
			if (str == NULL)
				flag = GNL_NULL;
			else
				flag = GNL_NOT_NULL;
			break ;
		}
		free(str);
		str = NULL;
	}
	if (flag == GNL_NOT_NULL)
	{
		free(str);
		str = NULL;
	}
	return (flag);
}

// static void	count_map_height(int tmep_fd)
// {

// }

static void	init_map_content(t_map_info *map_info, int this_fd, \
				char *file_path, size_t cnt_gnl)
{
	t_gnl_flag	gnl_flag;
	int			temp_fd;

	temp_fd = safe_open(file_path);
	pass_element(cnt_gnl, temp_fd);
	gnl_flag = pass_empty_line(temp_fd);
	if (gnl_flag == GNL_NULL)
		print_error_str("There is not a map!\n");
	// count_map_height(temp_fd);
	this_fd = 0;
	map_info = NULL;
	close(temp_fd);
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
	close(fd);
}
