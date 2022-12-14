/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikael <mikael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 09:14:59 by mikael            #+#    #+#             */
/*   Updated: 2022/08/14 18:02:45 by mikael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif


char*	join(char* s1, char* s2)
{
	char			*s3;
	unsigned int	i;
	unsigned int	j;

	if (!s1 && !s2)
		return (NULL);
	s3 = (char *)malloc(sizeof(*s3) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (0);
	i = 0;
	j = 0;
	 while (s1[i] != 0 && s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j] != 0)
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[i] = '\0';
	return (s3);
	}
	


char *remember_join_buffer(char* remembrall, int fd)
{
	char*	string;
	char*	buffer;
	char*	temp;
	int		red;

	string = NULL;
	buffer = malloc(sizeof(char)*BUFFER_SIZE + 1);

	if (!buffer)
		return (0);
	red = BUFFER_SIZE;
	buffer[red] = '\0';
	if (remembrall)
		string = ft_strlcpy2(string, remembrall);
	else if (!remembrall)	
		string = ft_strlcpy2(string, buffer);
	while(red > 0 && check_backslash_n(string) == 0 && string)
	{
		temp = string;
		red = read(fd, buffer, BUFFER_SIZE);
		if (red == 0)
		{
			free (string);
			free (buffer);
			return (NULL);
		}
		string = join(string, buffer);
		free (temp);
	} 
	free (buffer);
 	return (string);
}

char*	keeping_memory(char* middle_string)
{
	char*	string;
	int		i;
	int 	j;
		
	i = 0;
	if (ft_strlen(middle_string) == 1)
		j = 1;
	else
		j = ft_count_buffer(middle_string) - ft_strlen(middle_string);
	if (j < 0)
		j = j * -1;
	string = malloc(sizeof(char) * j + 1);
	if(!string)
		return (0);
	while(middle_string[i])
	{
		if(middle_string[i] == '\n')
		{
			i++;
			j = 0;
			while(middle_string[i] != '\0' && middle_string)
			{
				string[j] = middle_string[i];
				i++;
				j++;
			}
			i--;
		}
		i++;
	}
	string[j] = '\0';
	return (string);
}

char*	clean_it(char* string)
{
	int i;
	char*	str_return;
		
	i = ft_count_buffer(string);
	str_return = malloc(sizeof(char)*i + 1);
	if (!str_return)
		return (0);
	i = 0;
	if (string[0] == '\n')
		{
			str_return[0] = '\n';
			str_return[1] = '\0';
			return (str_return);
		}	
   	while (string[i] != '\n' && string[i] != '\0')
	{
		str_return[i] = string[i];
		i++;
		if(string[i] == '\n')
		{
			str_return[i] = '\n';
			str_return[++i] = '\0';	
			return (str_return);	
		}
	}
	return (0);
}

char*	get_next_line(int fd)
{
	static char*	remembrall;
	char*			middle_string;
	char*			final_string;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (NULL);
	middle_string = remember_join_buffer(remembrall, fd);
	if (!middle_string)
		{
		free(remembrall);
		return(NULL);
		}
	if (remembrall)
		free (remembrall);
	remembrall = keeping_memory(middle_string);
	final_string = clean_it(middle_string);
	free(middle_string);
	return (final_string);
}
/*
int main()
{
	char*	str;

	int fd;
	fd = open("text", O_RDONLY);
	if (fd == -1)
	{
		return (1);
	}
	str = get_next_line(fd);
	printf("%s", str);
	while(str)
	{   
		if (str)
			free(str);
		str = get_next_line(fd);
		printf("%s", str);
	}
	if (str)
		free(str);
   	close(fd); 
	system("leaks a.out");
	return (0);
}*/
