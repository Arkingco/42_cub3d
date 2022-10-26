/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayoon <jayoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:11:37 by jayoon            #+#    #+#             */
/*   Updated: 2022/10/17 13:15:55 by jayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define WRITE_ERROR_FD			2

int		exit_window(void *not_use);
void	exit_perror(void);
void	print_error_str(char *str);

#endif
