/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:01:26 by kipark            #+#    #+#             */
/*   Updated: 2022/10/13 16:06:30 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	game_start(char **map)
{
	void	*mlx;
	void	*mlx_win;
	t_param	param;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "cub3D");
	map = NULL;
	mlx_hook(mlx_win, EVENT_KEY_PRESS, 0, &key_press, &param);
	mlx_hook(mlx_win, X_EVENT_EXIT, 0, &exit_window, NULL);
	mlx_loop(mlx);
}

int	main(int argc, char **argv)
{
	t_list	*str_head;
	char	**map;

	if (argc != 2)
		print_error_str(EXIT_ERROR_PLAG, "Error\nArguments not match\n");
	str_head = NULL;
	map = parse(&str_head, argv);
	game_start(map);
}
