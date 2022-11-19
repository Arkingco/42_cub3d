/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:02:00 by kipark            #+#    #+#             */
/*   Updated: 2022/11/19 14:39:59 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "error.h"
#include "cub3d.h"
#include "game_view.h"

void	*my_mlx_xpm_file_to_image(void *xvar, char *file, int *width, \
																int *height)
{
	void	*img;

	img = mlx_xpm_file_to_image(xvar, file, width, height);
	if (img == NULL)
		print_error_str(MSG_ERR_MLX);
	return (img);
}

void	*my_mlx_init(void)
{
	void	*mlx;

	mlx = mlx_init();
	if (mlx == NULL)
		print_error_str(MSG_ERR_MLX);
	return (mlx);
}


void	*my_mlx_new_image(void *mlx_ptr, int width, int height)
{
	void	*img;

	img = mlx_new_image(mlx_ptr, width, height);
	if (img == NULL)
		print_error_str(MSG_ERR_MLX);
	return (img);
}
