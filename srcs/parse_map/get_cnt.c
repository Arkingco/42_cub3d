/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cnt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 21:59:06 by jayoon            #+#    #+#             */
/*   Updated: 2022/11/17 22:06:41 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_map.h"

static int	is_not_space_or_eol(char c)
{
	return (c != ' ' && c != '\n');
}

void	get_cnt(char c, t_get_map_cnt *cnt)
{
	if (is_not_space_or_eol(c))
		++cnt->cnt_valid_c;
	if (is_start_position(c))
		++cnt->cnt_start_pos;
}
