/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 11:44:06 by jayoon            #+#    #+#             */
/*   Updated: 2022/10/14 16:18:12 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_MAP_H
# define PARSE_MAP_H

enum e_direction
{
	EA = 0,
	WE,
	SO,
	NO
};

enum e_rgb
{
	R = 0,
	G,
	B
};

typedef struct s_map_info
{
	char	*texture[4];
	int		rgb_floor[3];
	int		rgb_ceilling[3];
	char	**map;
}   t_map_info;

#endif
