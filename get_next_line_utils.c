/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikael <mikael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:57:43 by mikael            #+#    #+#             */
/*   Updated: 2022/08/13 14:14:31 by mjonatha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"


// this function seeks the \n in buf en send back 1 if there is \n or 0 if not.
int check_backslash_n(char *buf)
{
	int i;

	i = 0;
	if (buf == NULL)
		return (0);
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int ft_strlen(const char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char*	ft_strlcpy2(char *dst,const char *src)
{
	int	i;
	int	len;

	len = ft_strlen(src);
	i = 0;
	dst = malloc(sizeof(char)*len + 1);
	if (!dst)
		return (NULL);
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}

int	ft_count_buffer(char * middle_string)
{
	int	i;

	i = 0;
	while (middle_string[i])
{
	if (middle_string[i] == '\n')
	{
		i++;
		return (i);
	}
	i++;
}
return (0);
}
