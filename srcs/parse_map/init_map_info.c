/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:04:54 by jayoon            #+#    #+#             */
/*   Updated: 2022/10/18 19:08:08 by jayoon           ###   ########.fr       */
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

static int	open_file(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		exit_perror();
	return (fd);
}

static void	init_arr(t_identifier *arr)
{
	int					i;
	enum e_identifier	num;

	i = 0;
	num = EAST;
	while (i < 4)
	{
		arr[i].len = 3;
		arr[i].identifier = num++;
		++i;
	}
	while (i < 6)
	{
		arr[i].len = 2;
		arr[i].identifier = num++;
		++i;
	}
	arr[0].str = "EA ";
	arr[1].str = "WE ";
	arr[2].str = "SO ";
	arr[3].str = "NO ";
	arr[4].str = "F ";
	arr[5].str = "C ";
}

static int	what_is_identifier(char *str)
{
	t_identifier	arr[6];
	int				i;

	i = 0;
	init_arr(arr);
	while (i < 6)
	{
		if (!ft_strncmp(str, arr[i].str, arr[i].len))
			return (arr[i].identifier);
		++i;
	}
	return (-1);
}

static int	is_identifier(char *str)
{
	while (*str != '\n')
	{
		if (*str != ' ')
			return (what_is_identifier(str));
		++str;
	}
	return (0);
}

static void	init_element(t_map_info *param, int fd)
{
	char	*str;

	param = NULL;
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		if (is_identifier(str) == -1)
			print_error_str("Invalid identifier\n");
		
	}
}

void	init_map_info(t_map_info *param, int argc, char *file_path)
{
	int	fd;

	if (check_argc(argc))
		print_error_str("Argument must be one\n");
	fd = open_file(file_path);
	param = NULL;
	init_element(param, fd);
	close(fd);
}
