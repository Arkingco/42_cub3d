/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:01:26 by kipark            #+#    #+#             */
/*   Updated: 2022/10/14 16:21:35 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_map.h"
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int	main(int argc, char *argv[])
{
	// t_map_info	map_info;
	
	argc = 0;
	argv = 0;
	if (argc != 2)
	// if (argc != 2)
	// {
		
	// }
	return (0);
}

// #include "so_long.h"

// static void	game_start(char **map)
// {
// 	void	*mlx;
// 	void	*mlx_win;
// 	t_param	param;

// 	mlx = mlx_init();
// 	mlx_win = mlx_new_window(mlx, 1920, 1080, "cub3D");
// 	map = NULL;
// 	mlx_hook(mlx_win, EVENT_KEY_PRESS, 0, &key_press, &param);
// 	mlx_hook(mlx_win, X_EVENT_EXIT, 0, &exit_window, NULL);
// 	mlx_loop(mlx);
// }

// int	main(int argc, char **argv)
// {
// 	t_list	*str_head;
// 	char	**map;

// 	if (argc != 2)
// 		print_error_str("Arguments not match\n");
// 	str_head = NULL;
// 	map = parse(&str_head, argv);
// 	game_start(map);
// }
