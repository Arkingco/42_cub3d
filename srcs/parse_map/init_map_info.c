/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:04:54 by jayoon            #+#    #+#             */
/*   Updated: 2022/10/18 21:33:45 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "error.h"
#include <fcntl.h>
#include "libft.h"
#include "parse_map.h"
#include <stdio.h>
#include <unistd.h>

static int	check_argc(int argc)
{
	return (argc != 2);
}

static int	safe_open(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		exit_perror();
	return (fd);
}

static t_num_iden	what_is_identifier(char *str)
{
	const t_identifier	arr[6] = {{"EA ", 3, EAST}, \
									{"WE ", 3, WEST}, \
									{"SO ", 3, SOUTH}, \
									{"NO ", 3, NORTH}, \
									{"F ", 2, FLOOR}, \
									{"C ", 2, CEILING}};
	int					i;

	i = 0;
	while (i < 6)
	{
		if (!ft_strncmp(str, arr[i].str, arr[i].len))
			return (arr[i].identifier);
		++i;
	}
	return (ELEMENT_FAIL);
}

static int	is_identifier(char *str)
{
	while (*str != '\n')
	{
		if (*str != ' ')
			return (what_is_identifier(str));
		++str;
	}
	return (ELEMENT_FAIL);
}

static void	init_element(t_map_info *param, int fd)
{
	char		*str;
	t_num_iden	num;

	param = NULL;
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		num = is_identifier(str);
		if (num == ELEMENT_FAIL)
			print_error_str("Invalid identifier\n");
		else if ()
	}
}

void	init_map_info(t_map_info *param, int argc, char *file_path)
{
	int	fd;

	if (check_argc(argc))
		print_error_str("Argument must be one\n");
	fd = safe_open(file_path);
	param = NULL;
	init_element(param, fd);
	close(fd);
}
