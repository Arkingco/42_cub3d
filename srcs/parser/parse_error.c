/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:31:52 by kipark            #+#    #+#             */
/*   Updated: 2022/10/30 14:16:48 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "error.h"
#include "unistd.h"

// static int	check_str_row_length(char **parsed_str)
// {
// 	int	length;

// 	length = 0;
// 	while (parsed_str[length] != NULL)
// 		length++;
// 	if (length >= 3)
// 		return (0);
// 	return (1);
// }

// static int	check_str_rectangle(char **parsed_str)
// {
// int	before_colum_length;
// int	idx;

// 	before_colum_length = get_column_length(parsed_str[0]);
// 	idx = 1;
// 	while (parsed_str[idx] != NULL)
// 	{
// 		if (before_colum_length != get_column_length(parsed_str[idx]))
// 			return (1);
// 		idx++;
// 	}
// 	return (0);
// }

// static int	check_wall_surrounded(char **parse_str, int colum_length)
// {
// 	int	mid;
// 	int	idx;
// 	int	bottom;

// 	mid = 1;
// 	bottom = get_row_length(parse_str) - 1;
// 	idx = 0;
// 	while (parse_str[0][idx] != '\0' && parse_str[0][idx] == '1')
// 		idx++;
// 	if (idx != colum_length)
// 		return (1);
// 	idx = 0;
// 	while (mid < bottom)
// 	{
// 		if (parse_str[mid][0] != '1' || parse_str[mid][colum_length - 1] != '1')
// 			return (1);
// 		mid++;
// 	}
// 	idx = 0;
// 	while (parse_str[bottom][idx] != '\0' && parse_str[bottom][idx] == '1')
// 		idx++;
// 	if (idx != colum_length)
// 		return (1);
// 	return (0);
// }

#include <stdio.h>
int	parsed_str_error_check(char **parsed_str)
{
	// if (check_str_row_length(parsed_str))
	// 	print_error_str("row_under_3\n");
	// if (check_str_rectangle(parsed_str))
	// 	print_error_str("not_rectangle\n");
	// if (check_wall_surrounded(parsed_str, get_column_length(parsed_str[0])))
	// 	print_error_str("not_wal_surrounded\n");
	printf("%s \n", parsed_str[0]);
	return (0);
}
