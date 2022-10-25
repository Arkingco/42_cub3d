/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 21:22:01 by jayoon            #+#    #+#             */
/*   Updated: 2022/10/25 20:10:29 by jayoon           ###   ########.fr       */
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

static size_t	count_map_height(int temp_fd)
{
	size_t	height;
	char	*str;

	height = 1;
	str = NULL;
	while (1)
	{
		str = get_next_line(temp_fd);
		if (str == NULL || *str == '\n')
			break ;
		++height;
		free(str);
		str = NULL;
	}
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
	return (height);
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
		print_error_str("There is not a map!\n");
	map_info->map_height = count_map_height(temp_fd);
	str = pass_empty_line(temp_fd);
	close(temp_fd);
	if (str != NULL)
		print_error_str("There must be not anything under the map!\n");
	temp_map = init_temp_map(map_info, this_fd);
	close(this_fd);


	size_t	i = 0;
	while (temp_map[i])
	{
		printf("%s", temp_map[i]);
		i++;
	}
	// map_info->map_withd = count_map_width(temp_map);
	//free_temp_map()
	/**
	 * 가장 긴 width 구함
	 * 0 1 E W S N 만 있는지 확인 (이것을 확인할 것이면 굳이 재귀적으로 도는 것이 좋나? 고민)
	 * 구한 길이대로 이차원 배열 생성
	 */
}
