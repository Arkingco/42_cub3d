/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:58:52 by jayoon            #+#    #+#             */
/*   Updated: 2022/10/17 12:26:31 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_MAP
# define PARSE_MAP

enum e_direction
{
	EA,
	WE,
	SO,
	NO
};

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

#endif
