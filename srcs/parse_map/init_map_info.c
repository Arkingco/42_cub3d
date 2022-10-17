/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:04:54 by jayoon            #+#    #+#             */
/*   Updated: 2022/10/17 17:21:28 by jayoon           ###   ########.fr       */
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
	i = 0;
	while (i < 6)
	{
		printf("%d: %s, %zu, %d\n", i, arr[i].str, arr[i].len, arr[i].identifier);
		++i;
	}
}

static int	what_is_identifier(char *str)
{
	t_identifier	arr[6];

	init_arr(arr);
	if (!ft_strncmp(str, "EA ", 3))
		return (EAST);
	else if (!ft_strncmp(str, "WE ", 3))
		return (WEST);
	else if (!ft_strncmp(str, "SO ", 3))
		return (SOUTH);
	else if (!ft_strncmp(str, "NO ", 3))
		return (NORTH);
	else if (!ft_strncmp(str, "F ", 2))
		return (FLOOR);
	else if (!ft_strncmp(str, "C ", 2))
		return (CEILING);
	return (0);
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
		if (!is_identifier(str))
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
