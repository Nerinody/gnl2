#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get_next_line.h"



char*	count(char* str)
{
	int i = 0;
	int j = 0;
	int taille = ft_count_buffer(str) - ft_strlen(str);
	if (taille < 0)
		taille = taille * -1;
	char *string;
	string = malloc(sizeof(char)*taille + 1);

	while(str[i + j])
	{
		if (str[i + j] == '\n')
		{
			i++;
			while(str[i + j])
			{
				string[j] = str[j + i];
				j++;
			}
		}
		i++;
	}
	string[j] = '\0';
	return (string);
}

int main()
{
	char	string[] = "petite patate  \n  jolie tout plein";
	char*	string2;

	
	string2 = count(string);

	printf("%s\n", string2);
	free (string2);
	
	return (0);
}