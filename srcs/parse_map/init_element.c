/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_element.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:10:49 by jayoon            #+#    #+#             */
/*   Updated: 2022/10/29 18:12:11 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "parse_map.h"

static t_identifier	check_identifier(t_map_info *map_info, char *str)
{
	const t_identifier_info	arr[6] = \
					{{"EA ", CNT_WORD_OF_TEXTRUE, EAST, process_texture_path}, \
					{"WE ", CNT_WORD_OF_TEXTRUE, WEST, process_texture_path}, \
					{"SO ", CNT_WORD_OF_TEXTRUE, SOUTH, process_texture_path}, \
					{"NO ", CNT_WORD_OF_TEXTRUE, NORTH, process_texture_path}, \
					{"F ", CNT_WORD_OF_COLOR, FLOOR, process_color}, \
					{"C ", CNT_WORD_OF_COLOR, CEILING, process_color}};
	int						i;

	i = 0;
	while (i < CNT_IDENTIFIER)
	{
		if (!ft_strncmp(str, arr[i].str, arr[i].len))
			return (arr[i].f_parsing(map_info, str, arr[i].identifier));
		++i;
	}
	return (ELEMENT_FAIL);
}

static void	change_eol_to_nul(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			*str = '\0';
		++str;
	}
}

/*
 * First word followd zero or some space is identifier.
 */
static t_identifier	parse_string(t_map_info *map_info, char *str)
{
	t_identifier	identifier;

	identifier = ELEMENT_FAIL;
	change_eol_to_nul(str);
	while (*str)
	{
		if (*str != ' ')
			return (check_identifier(map_info, str));
		++str;
	}
	return (identifier);
}

/*
 * If first character is not eol, that identifier will be checked.
 */
size_t	init_element(t_map_info *map_info, int fd)
{
	char	*str;
	size_t	cnt_element;	
	size_t	cnt_gnl;

	cnt_element = 0;
	cnt_gnl = 0;
	while (1)
	{
		if (cnt_element == CNT_IDENTIFIER)
			break ;
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		++cnt_gnl;
		if (*str != '\n')
		{
			if (parse_string(map_info, str) == ELEMENT_FAIL)
				print_error_str(MSG_ERR_IDNETIFIER);
			++cnt_element;
		}
		free(str);
		str = NULL;
	}
	return (cnt_gnl);
}
