/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_texture_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:21:30 by jayoon            #+#    #+#             */
/*   Updated: 2022/10/29 18:10:27 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "parse_map.h"

static void	init_texture_path_variable(t_substr_info *info, char **p_str)
{
	info->start = NULL;
	info->end = NULL;
	info->flag = 0;
	*p_str = *p_str + 3;
}

t_identifier	process_texture_path(t_map_info *map_info, char *str, \
						t_identifier num_iden)
{
	t_substr_info	info;

	init_texture_path_variable(&info, &str);
	while (*str)
	{
		if (*str != ' ')
		{
			if (info.end != NULL)
				print_error_str(MSG_ERR_ELEMENT);
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
		print_error_str(MSG_ERR_ELEMENT);
	return (num_iden);
}
