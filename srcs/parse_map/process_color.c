/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:14:07 by jayoon            #+#    #+#             */
/*   Updated: 2022/10/24 13:29:36 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "parse_map.h"

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
t_identifier	process_color(t_map_info *map_info, char *str, \
						t_identifier num_iden)
{
	t_substr_info	info;
	size_t			cnt_comma;

	info.start = NULL;
	info.end = NULL;
	info.flag = 0;
	str = str + 2;
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
