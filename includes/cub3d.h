/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:57:19 by kipark            #+#    #+#             */
/*   Updated: 2022/10/13 17:30:38 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define EVENT_KEY_PRESS		2
# define X_EVENT_EXIT			17
# define KEY_ESC				53
# define KEY_W					13
# define KEY_A					0
# define KEY_S					1
# define KEY_D					2
# define WRITE_ERROR_FD			2
# define PX						64

# define EXIT_ERROR_PLAG		1

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_list
{
	struct s_list	*next;
	char			*str;
}				t_list;

typedef struct s_player
{
	int y;
	int x;
}	t_player;

int		gnl_strchr(char *s, char word);
int		gnl_strlen(char *s);
char	*gnl_strjoin(char *static_line, char *buffer, int buffer_length);
void	gnl_free_char_pointer(char **pointer);

char	*get_next_line(int fd);

int		get_list_head_colum(char *head_str);
int		get_list_head_row(t_list *list_head);

void	print_error(int exit_flag);
void	print_error_str(int exit_flag, char *str);
void	set_parsed_str(char *parsed_str, char *head_str);

int		parsed_str_error_check(char **parsed_str);
int		get_column_length(char *str);
int		get_row_length(char **str);
char	*so_long_strjoin(char *buffer);

char	**parse(t_list **str_head, char **argv);
void	set_background(void *mlx, void *mlx_win);

int		exit_window(void *not_use);

#endif
