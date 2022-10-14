/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:27:47 by kipark            #+#    #+#             */
/*   Updated: 2022/10/14 16:18:02 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

int	exit_window(void *not_use)
{
	(void)not_use;
	exit(0);
}

void	print_error_str(char *str)
{
	write(WRITE_ERROR_FD, "Error\n", ft_strlen("Error\n"));
	if (str != NULL)
		write(WRITE_ERROR_FD, str, ft_strlen(str));
	exit(1);
}
