/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikael <mikael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:03:21 by mikael            #+#    #+#             */
/*   Updated: 2022/08/14 17:49:47 by mikael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

char*  ft_strlcpy2(char *dst, const char *src);
int ft_strlen(const char *str);
int check_backslash_n(char *buf);
int	ft_count_buffer(char * middle_string);
char*   get_next_line(int fd);

#endif
