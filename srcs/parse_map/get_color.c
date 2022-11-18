/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 20:51:49 by jayoon            #+#    #+#             */
/*   Updated: 2022/11/18 20:52:41 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "parse_map.h"

static void	check_0_to_255(int num)
{
	if (num < 0 || num > 255)
		print_error_str(MSG_ERR_ELEMENT);
}

static int	make_color_info(int color_info, int num, int i)
{
	color_info |= num;
	if (i < 2)
		color_info <<= 8;
	return (color_info);
}

void	get_color(t_map_info *map_info, t_identifier num_iden, char *str)
{
	char	**arr_rgb;
	int		num;
	int		i;

	i = 0;
	arr_rgb = ft_split(str, ',');
	while (arr_rgb[i])
	{
		num = cub3d_atoi(arr_rgb[i]);
		if (num == -1)
			print_error_str(MSG_ERR_ELEMENT);
		check_0_to_255(num);
		if (num_iden == FLOOR)
			map_info->floor_info \
				= make_color_info(map_info->floor_info, num, i);
		else
			map_info->ceiling_info \
				= make_color_info(map_info->ceiling_info, num, i);
		++i;
	}
	if (i != 3)
		print_error_str(MSG_ERR_ELEMENT);
	ft_safe_free_two_dimentions_arr(arr_rgb);
}
