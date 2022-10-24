/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 21:22:01 by jayoon            #+#    #+#             */
/*   Updated: 2022/10/24 21:31:53 by jayoon           ###   ########.fr       */
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

void	init_map_content(t_map_info *map_info, int this_fd, \
				char *file_path, size_t cnt_gnl)
{
	t_gnl_flag	gnl_flag;
	int			temp_fd;

	temp_fd = safe_open(file_path);
	pass_element(cnt_gnl, temp_fd);
	gnl_flag = pass_empty_line(temp_fd);
	if (gnl_flag == GNL_NULL)
		print_error_str("There is not a map!\n");
	map_info->map_height = count_map_height(temp_fd);
	/**
	 * 맵 이후에 있는 개행, 붙어있지 않은 맵, 유효하지 않은 문자 검사
	 * map content가 정상이라면 map_height만큼 malloc한 뒤 gnl 반환값 넣기
	 * 가장 긴 문자열을 찾아 map_width에 넣고 height x width 크기의 배열 할당 받는다.
	 * memset으로 공백 채우기
	 * 이후 기존 map 을 넣기
	 * 맵 구성 요소 검사
	 */
	//test
	this_fd = 0;
	map_info = NULL;
	close(temp_fd);
}
