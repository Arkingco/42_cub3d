/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:54:19 by kipark            #+#    #+#             */
/*   Updated: 2022/10/13 16:44:33 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "unistd.h"

int	get_column_length(char *str)
{
	int	idx;

	idx = 0;
	if (str == NULL)
		return (0);
	while (str[idx] != '\0')
		idx++;
	return (idx);
}

int	get_row_length(char **str)
{
	int	idx;

	idx = 0;
	while (str[idx] != NULL)
		idx++;
	return (idx);
}
