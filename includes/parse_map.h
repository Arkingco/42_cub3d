/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:58:52 by jayoon            #+#    #+#             */
/*   Updated: 2022/11/15 22:57:20 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_MAP_H
# define PARSE_MAP_H

# define CNT_TEXTURE			4
# define CNT_COLOR				3

# define CNT_IDENTIFIER			6

# define CNT_WORD_OF_TEXTRUE	3
# define CNT_WORD_OF_COLOR		2

# define MSG_ERR_ARGS			"Argument must be one!\n"
# define MSG_ERR_FILE_NAME		"File name is invalid!\n"
# define MSG_ERR_ELEMENT		"Invalid element!\n"
# define MSG_ERR_IDNETIFIER		"Invalid identifier!\n"
# define MSG_ERR_MAP			"Invalid map!\n"

# define INT_MAX				2147483647

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

typedef enum e_gnl_flag
{
	GNL_NULL,
	GNL_NOT_NULL
}	t_gnl_flag;

typedef enum e_cub_bool
{
	CUB_FAIL,
	CUB_SUCCESS
}	t_cub_bool;

typedef enum e_cnt_start_position
{
	CUB_ZERO,
	CUB_ONE
}	t_cnt_start_pos;

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
	size_t	map_width;
	size_t	map_height;
}	t_map_info;

typedef struct s_identifier_info
{
	char			*str;
	size_t			len;
	t_identifier	identifier;
	t_identifier	((*f_parsing)(t_map_info *, char *, t_identifier));
}	t_identifier_info;

typedef struct s_get_map_cnt
{
	size_t	cnt_start_pos;
	size_t	cnt_valid_c;
}	t_get_map_cnt;

/* main */
void			init_map_info(t_map_info *param, int argc, char *file_path);
size_t			init_element(t_map_info *map_info, int fd);
void			init_map_content(t_map_info *map_info, int this_fd, \
					char *file_path, size_t cnt_gnl);
t_identifier	process_color(t_map_info *map_info, char *str, \
						t_identifier num_iden);
t_identifier	process_texture_path(t_map_info *map_info, char *str, \
						t_identifier num_iden);
size_t			get_map(t_map_info *map_info, char **temp_map);

/* utils */
int				cub3d_atoi(const char *str);
int				safe_open(char *file_path);
void			pass_element(size_t cnt_gnl, int temp_fd);
char			*pass_empty_line(int fd);
size_t			get_cnt_map_height(int temp_fd);
size_t			get_cnt_map_width(char **map);
t_cnt_start_pos	is_valid_map(t_map_info *map_info);
int				is_valid_character(char c);

#endif
