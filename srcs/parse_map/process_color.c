/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:14:07 by jayoon            #+#    #+#             */
/*   Updated: 2022/11/18 20:51:57 by jayoon           ###   ########.fr       */
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
		print_error_str(MSG_ERR_ELEMENT);
	return (num_iden);
}
