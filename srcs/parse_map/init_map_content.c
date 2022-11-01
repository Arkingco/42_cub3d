/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 21:22:01 by jayoon            #+#    #+#             */
/*   Updated: 2022/10/29 20:45:57 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "parse_map.h"

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

static char	*pass_empty_line(int fd)
{
	char		*str;

	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL || *str != '\n')
			break ;
		free(str);
		str = NULL;
	}
	return (str);
}

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

// static int	check_valid_character(char c, size_t y, size_t x)
// {
// 	if (c == '1')
// 	{

// 	}
// }

static void	get_map(t_map_info *map_info, char **temp_map)
{
	size_t	i;
	size_t	j;

	map_info->map = ft_safe_malloc(sizeof(char *) * (map_info->map_height + 1));
	i = 0;
	while (map_info->map_height > i)
	{
		j = 0;
		map_info->map[i] = ft_safe_malloc(map_info->map_width + 1);
		while (temp_map[i][j] != '\n' && temp_map[i][j] != '\0')
		{
			map_info->map[i][j] = temp_map[i][j];
			// if (check_valid_character(map_info->map[i][j], i, j))
			// 	print_error_str(MSG_ERR_MAP);
			++j;
		}
		while (map_info->map_width > j)
		{
			map_info->map[i][j] = ' ';
			++j;
		}
		map_info->map[i][j] = '\0';
		++i;
	}
	map_info->map[i] = NULL;
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
