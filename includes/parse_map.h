/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:58:52 by jayoon            #+#    #+#             */
/*   Updated: 2022/10/19 21:57:49 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_MAP
# define PARSE_MAP

# include <stdlib.h>

typedef enum e_num_iden
{
	EAST,
	WEST,
	SOUTH,
	NORTH,
	FLOOR,
	CEILING,
	ELEMENT_FAIL
}	t_num_iden;

enum e_color
{
	R,
	G,
	B
};

typedef struct s_map_info
{
	char	*texture_path[4];
	int		floor[3];
	int		ceilling[3];
	char	**map;
}	t_map_info;

typedef struct s_identifier
{
	char		*str;
	size_t		len;
	t_num_iden	identifier;
	t_num_iden	(*f_parsing)(t_map_info *, char *, t_num_iden);
}	t_identifier;

void	init_map_info(t_map_info *param, int argc, char *file_path);

#endif
