/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:54:32 by jayoon            #+#    #+#             */
/*   Updated: 2022/11/15 22:54:32 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"

int	cub3d_atoi(const char *str)
{
	size_t	res;

	res = 0;
	while (*str)
	{
		if (ft_isdigit(*str))
			res = 10 * res + *str - '0';
		else
			return (-1);
		if (res > INT_MAX)
			return (-1);
		++str;
	}
	return ((int)res);
}
