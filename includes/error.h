/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipark <kipark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:11:37 by jayoon            #+#    #+#             */
/*   Updated: 2022/11/19 14:36:56 by kipark           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define WRITE_ERROR_FD			2
# define MSG_ERR_MLX    		"MLX NULL POINTER RETURN!\n"

int		exit_window(void *not_use);
void	exit_perror(void);
void	print_error_str(char *str);

#endif
