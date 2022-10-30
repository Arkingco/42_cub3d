/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_element.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:10:49 by jayoon            #+#    #+#             */
/*   Updated: 2022/10/24 16:30:27 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "parse_map.h"

static t_identifier	check_identifier(t_map_info *map_info, char *str)
{
	const t_identifier_info	arr[6] = {{"EA ", 3, EAST, process_texture_path}, \
									{"WE ", 3, WEST, process_texture_path}, \
									{"SO ", 3, SOUTH, process_texture_path}, \
									{"NO ", 3, NORTH, process_texture_path}, \
									{"F ", 2, FLOOR, process_color}, \
									{"C ", 2, CEILING, process_color}};
	int						i;

	i = 0;
	while (i < 6)
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
		if (cnt_element == 6)
			break ;
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		++cnt_gnl;
		if (*str != '\n')
		{
			if (parse_string(map_info, str) == ELEMENT_FAIL)
				print_error_str("Invalid identifier\n");
			++cnt_element;
		}
		free(str);
		str = NULL;
	}
	return (cnt_gnl);
}
