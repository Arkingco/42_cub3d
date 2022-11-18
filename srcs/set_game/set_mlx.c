/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:02:00 by kipark            #+#    #+#             */
/*   Updated: 2022/11/18 21:36:57 by kipark           ###   ########seoul.kr  */
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
		print_error_str(MSG_ERR_ELEMENT);
	return (img);
}
