/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cnt_map_height.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:48:43 by jayoon            #+#    #+#             */
/*   Updated: 2022/11/18 18:20:44 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "parse_map.h"

size_t	get_cnt_map_height(int temp_fd)
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
	if (height > 65)
		print_error_str(MSG_ERR_MAP_IS_BIG);
	return (height);
}
