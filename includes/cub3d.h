/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:57:19 by kipark            #+#    #+#             */
/*   Updated: 2022/11/18 16:44:20 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "struct.h"
# include "minimap.h"
# include "parse_map.h"

# define EXIT_ERROR_PLAG		1
# define WRITE_ERROR_FD			2
# define GAME_WIDTH				1500
# define GAME_HEIGHT			1000

int		gnl_strchr(char *s, char word);
int		gnl_strlen(char *s);
char	*gnl_strjoin(char *static_line, char *buffer, int buffer_length);
void	gnl_free_char_pointer(char **pointer);

char	*get_next_line(int fd);

int		get_list_head_colum(char *head_str);
int		get_list_head_row(t_list_so_long *list_head);

void	set_parsed_str(char *parsed_str, char *head_str);

int		parsed_str_error_check(char **parsed_str);
int		get_column_length(char *str);
int		get_row_length(char **str);
char	*so_long_strjoin(char *buffer);

char	**parse(t_list_so_long **str_head, char **argv);
void	set_background(void *mlx, void *mlx_win);

void	set_player(t_game *game);
void	set_game(t_game *game, t_map_info *map_info);
void	set_texture(t_game *game);

#endif
