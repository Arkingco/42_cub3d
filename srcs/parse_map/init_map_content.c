/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 21:22:01 by jayoon            #+#    #+#             */
/*   Updated: 2022/11/10 20:20:17 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "parse_map.h"

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
	if (get_map(map_info, temp_map) == 0)
		print_error_str(MSG_ERR_MAP);
	ft_safe_free_two_dimentions_arr(temp_map);
}
