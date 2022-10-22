/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:58:52 by jayoon            #+#    #+#             */
/*   Updated: 2022/10/22 17:41:52 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_MAP
# define PARSE_MAP

# include <stdlib.h>

typedef enum e_identifier
{
	EAST,
	WEST,
	SOUTH,
	NORTH,
	FLOOR,
	CEILING,
	ELEMENT_FAIL
}	t_identifier;

typedef enum e_color
{
	RED,
	GREEN,
	BLUE
}	t_color;

/**
 * Not used
typedef struct s_map_content
{
	char	**map;
	size_t	width;
	size_t	height;
}	t_map_content;
 */

typedef struct s_substr_info
{
	char	*start;
	char	*end;
	int		flag;
}	t_substr_info;

typedef struct s_map_info
{
	char	*texture_path[4];
	int		ceiling[3];
	int		floor[3];
	char	**map;
}	t_map_info;

typedef struct s_identifier_info
{
	char			*str;
	size_t			len;
	t_identifier	identifier;
	t_identifier	(*f_parsing)(t_map_info *, char *, t_identifier);
}	t_identifier_info;

void	init_map_info(t_map_info *param, int argc, char *file_path);
int		cub3d_atoi(const char *str);

#endif
