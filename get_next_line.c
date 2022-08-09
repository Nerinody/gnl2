/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikael <mikael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 09:14:59 by mikael            #+#    #+#             */
/*   Updated: 2022/08/09 17:30:01 by mjonatha         ###   ########.fr       */
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
	s3[i] = 0;
	return (s3);
	}
	


char *remember_join_buffer(char* remembrall, int fd)
{
	char*	string;
	char*	string_return;
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
	while(red > 0 && check_backslash_n(string) == 0)
	{
		temp = string;
		red = read(fd, buffer, BUFFER_SIZE);
		string = join(string, buffer);
		free (temp);
	} 
	free (buffer);
	string_return = malloc(sizeof(char)*ft_strlen(string) + 1);
	if(!string_return)
		return (0);	
string_return = ft_strlcpy2(string_return, string);
	free (string);
 	return (string_return);
}

char*	keeping_memory(char* middle_string)
{
	char*	string;
	int		i;
	int 	j;
		
	i = 0;
	j = ft_count_buffer(middle_string) - ft_strlen(middle_string);
	if(j < 0)
		j = i * -1;
	string = malloc(sizeof(char)*j + 2);
	if(!string)
		return (0);
	while(middle_string[i])
	{
		if(middle_string[i] == '\n')
		{
			i++;
			j = 0;
			while(middle_string[i] != '\0')
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
	int j;
	char*	str_return;
		
	j = 0;
	i = ft_count_buffer(string);
	str_return = malloc(sizeof(char)*i + 1);
	if (!str_return)
		return (0);
	i = 0;
   	while (string[i] != '\n' && string[i] != '\0')
	{
		str_return[j] = string[i];
		i++;
		j++;
		if(string[i] == '\n')
		{
			str_return[j] = string[i];
		   j++;
	    }	   
	}
	str_return[j] = '\0';
	return(str_return);
}


char *get_next_line(int fd)
{
	static char*	remembrall;
	char*			middle_string;
	char*			final_string;
	
	middle_string = remember_join_buffer(remembrall, fd);
//	printf("middle : %s\n", middle_string);
	remembrall = keeping_memory(middle_string);
//	printf("rem : %s\n", remembrall);
	//there is a leak in keeping_memory maybe i can use the fact that remembrall is a static. In that way i just call the function 
	//keeping_memory and put what i need in the static.
	final_string = clean_it(middle_string);
	free (middle_string);
	//printf("final : %s", final_string);
	return (final_string);
}

int main()
{
	int i = 7;
	char*	str;

	int fd;
	fd = open("text", O_RDONLY);
	if (fd == -1)
	{
		return (1);
	}
	while(i > 0)
	{
		str = get_next_line(fd);
		printf("%s", str);
		free (str);
		i--;
	}

	system("leaks a.out");
	return (0);
}
