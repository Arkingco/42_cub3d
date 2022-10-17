/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:27:47 by kipark            #+#    #+#             */
/*   Updated: 2022/10/17 12:33:43 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

int	exit_window(void *not_use)
{
	(void)not_use;
	exit(0);
}

void	print_error_str(char *str)
{
	write(WRITE_ERROR_FD, "ERROR\n", ft_strlen("ERROR\n"));
	if (str != NULL)
		write(WRITE_ERROR_FD, str, ft_strlen(str));
	exit(1);
}
