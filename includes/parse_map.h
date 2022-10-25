/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:58:52 by jayoon            #+#    #+#             */
/*   Updated: 2022/10/24 21:27:30 by jayoon           ###   ########.fr       */
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

typedef enum e_gnl_flag
{
	GNL_NULL,
	GNL_NOT_NULL
}	t_gnl_flag;

typedef struct s_map_info
{
	char	*texture_path[4];
	int		ceiling[3];
	int		floor[3];
	char	**map;
	size_t	map_withd;
	size_t	map_height;
}	t_map_info;

typedef struct s_identifier_info
{
	char			*str;
	size_t			len;
	t_identifier	identifier;
	t_identifier	(*f_parsing)(t_map_info *, char *, t_identifier);
}	t_identifier_info;

void			init_map_info(t_map_info *param, int argc, char *file_path);
int				cub3d_atoi(const char *str);
size_t			init_element(t_map_info *map_info, int fd);
t_identifier	process_color(t_map_info *map_info, char *str, \
						t_identifier num_iden);
t_identifier	process_texture_path(t_map_info *map_info, char *str, \
						t_identifier num_iden);
void			init_map_content(t_map_info *map_info, int this_fd, \
					char *file_path, size_t cnt_gnl);
int				safe_open(char *file_path);

#endif
