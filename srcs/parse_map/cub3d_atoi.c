/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:54:32 by jayoon            #+#    #+#             */
/*   Updated: 2022/10/21 19:17:45 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"

// 1. 1112a111 
// 2. 334   7777
// 3.           8 . 6 6298
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
			break ;
		++str;
	}
	if (flag == 1)
	{

	}
	else
		print_error_str("It is not number!\n");
	return (res);
}
