/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikael <mikael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 09:14:59 by mikael            #+#    #+#             */
/*   Updated: 2022/08/08 16:41:54 by mikael           ###   ########.fr       */
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
	//char*	temp;
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
		//string = malloc(sizeof(char)*)
	while(red > 0 && check_backslash_n(string) == 0)
	{
		//temp = string;
		red = read(fd, buffer, BUFFER_SIZE);
		string = join(string, buffer);
		
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
	/* j ai a resoudre le probleme avec le retour de l adresse de i, pour l utiliser et dire a string de 
	recup ce qu il y a apres cette adresse */
	char*	string;
	int		i;
	int 	j;
	
	i = 0;
	j = ft_count_buffer(middle_string) - ft_strlen(middle_string);
	if(i < 0)
		j = i * -1;
	string = malloc(sizeof(char)*200);
	if(!string)
		return(0);
	while(middle_string[i])
	{
		if(middle_string[i] == '\n')
		{
			i++;
			j = 0;
			while(middle_string[i])
				{
					string[j] = middle_string[i++];
					j++;
				}
		i--;
		}
	i++;
	}
	string[j] = '\0';
return (string);
}

/*char*	clean_it(char* string)
{
	int i;

	i = ft_count_buffer*
	
}
*/

char *get_next_line(int fd)
{
	static char*	remembrall;
	char*			middle_string;
	
	middle_string = remember_join_buffer(remembrall, fd); // takes what s left in remembrall from past call en join with buffer;
	remembrall = keeping_memory(middle_string);
	//middle_string = clean_it(middle_string);
	return (middle_string);
}

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
	printf("print 1 : %s \n", str);
	free (str);
	str = get_next_line(fd);
	printf("print 2 : %s \n", str);
	free (str);
	system("leaks a.out");
	return (0);
}
