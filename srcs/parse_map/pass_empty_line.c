/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass_empty_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 03:50:20 by jayoon            #+#    #+#             */
/*   Updated: 2022/11/05 03:50:39 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*pass_empty_line(int fd)
{
	char		*str;

	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL || *str != '\n')
			break ;
		free(str);
		str = NULL;
	}
	return (str);
}
