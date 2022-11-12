/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:27:47 by kipark            #+#    #+#             */
/*   Updated: 2022/10/26 20:34:59 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <errno.h>
// #include "error.h
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*str)
	{
		++len;
		++str;
	}
	return (len);
}

int	exit_window(void *not_use)
{
	(void)not_use;
	exit(0);
}

void	exit_perror(void)
{
	perror("Error\n");
	exit(1);
}

void	print_error_str(char *str)
{
	ssize_t	ret;

	ret = write(WRITE_ERROR_FD, "ERROR\n", ft_strlen("ERROR\n"));
	if (ret == -1)
		perror("cub3d :");
	if (str != NULL)
	{	
		ret = write(WRITE_ERROR_FD, str, ft_strlen(str));
		if (ret == -1)
			perror("cub3d :");
	}
	exit(1);
}
