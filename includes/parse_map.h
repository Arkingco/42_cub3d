/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:58:52 by jayoon            #+#    #+#             */
/*   Updated: 2022/10/17 20:17:44 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_MAP
# define PARSE_MAP

enum e_identifier
{
	EAST,
	WEST,
	SOUTH,
	NORTH,
	FLOOR,
	CEILING
};

enum e_color
{
	R,
	G,
	B
};

typedef struct s_identifier
{
	char				*str;
	size_t				len;
	enum e_identifier	identifier;
}	t_identifier;

typedef struct s_map_info
{
	char	*texture_path[4];
	int		floor[3];
	int		ceilling[3];
	char	**map;
}	t_map_info;

void	init_map_info(t_map_info *param, int argc, char *file_path);

#endif
