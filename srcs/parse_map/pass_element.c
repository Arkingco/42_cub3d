/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass_element.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 03:47:01 by jayoon            #+#    #+#             */
/*   Updated: 2022/11/05 03:49:11 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	pass_element(size_t cnt_gnl, int temp_fd)
{
	size_t	i;
	char	*str;

	i = 0;
	str = NULL;
	while (cnt_gnl > i)
	{
		str = get_next_line(temp_fd);
		free(str);
		str = NULL;
		++i;
	}
}
