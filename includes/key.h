/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:53:28 by kipark            #+#    #+#             */
/*   Updated: 2022/11/16 22:29:06 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_H
# define KEY_H

# include "cub3d.h"
# include "minimap.h"

# define EVENT_KEY_PRESS		2
# define EVENT_KEY_RELEASE		3
# define X_EVENT_EXIT			17
# define KEY_ESC				53
# define KEY_W					13
# define KEY_A					0
# define KEY_S					1
# define KEY_D					2
# define PX						64
# define RIGHT_ARROR_KEY		123
# define LEFT_ARROR_KEY		124
# define D_PI (PI / 2)
# define A_PI (-PI / 2)
# define WALL_DIST 3

int	key_press(int keycode, t_game *param);

#endif
