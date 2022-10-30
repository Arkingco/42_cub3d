/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:54:32 by jayoon            #+#    #+#             */
/*   Updated: 2022/10/22 18:02:36 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"

int	cub3d_atoi(const char *str)
{
	int	res;
	int	flag;

	res = 0;
	flag = 0;
	while (*str)
	{
		if (ft_isdigit(*str))
		{
			res = 10 * res + *str - '0';
			flag = 1;
		}
		else
			return (-1);
		++str;
	}
	return (res);
}
