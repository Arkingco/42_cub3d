/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:27:47 by kipark            #+#    #+#             */
/*   Updated: 2022/10/12 11:27:52 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	exit_window(void *not_use)
{
	(void)not_use;
	exit(0);
}

void	print_error(int exit_flag)
{
	write(WRITE_ERROR_FD, "Error\n", 6);
	exit(exit_flag);
}

void	print_error_str(int exit_flag, char *str)
{
	write(WRITE_ERROR_FD, str, get_column_length(str));
	exit(exit_flag);
}
