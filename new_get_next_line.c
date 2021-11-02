/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_get_next_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchernyu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:55:12 by mchernyu          #+#    #+#             */
/*   Updated: 2021/11/02 19:36:51 by mchernyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 7

#include "get_next_line.h"

char *ft_search(char *buff, char c, int size, int *length)
{
	int i;

	i = 0;

	while (size > 0)
	{
		 if (buff[i] == c)
		 {
			 *length = i;
			 return (&buff[i]);
		 }
		 i++;
		 size--;
	}
	*length = i;
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*dst;
	int i;

	i = 0;
	dst = malloc(ft_strlen(s1) + 1);
	if (dst == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!result)
		return (NULL);
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		result[i] = s2[j];
		i++;
		j++;
	}
	result[i] = '\0';
	return (result);
}
char * ft_copy_in(char *result, char *buff, int length)
{
	int i;

	i = 0;
	result = malloc(length + 1);
	if (!result)
		return (NULL);
	while (i <= length)
	{
		result[i] = buff[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char *get_next_line(int fd)
{
	char *result;
	char buff[BUFFER_SIZE + 1];
	static char *remainder;
	int length;
	int read_bytes;

	//check remainder//
	while (read(fd, buff, BUFFER_SIZE) >= 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if ((ft_search(buff, '\n', read_bytes, &length)) != NULL)
		{		
			result = ft_copy_in(result, buff, length);
			remainder = ft_copy_in(remainder, &buff[length], read_bytes - length);
		}
		else
			result = ft_strjoin(result, buff);
	}
	return (NULL);
}

int main(void)
{
	int fd;
	char *line;

	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s", line);

	line = get_next_line(fd);
	printf("%s", line);

	line = get_next_line(fd);
	printf("%s", line);

	line = get_next_line(fd);
	printf("%s", line);

	line = get_next_line(fd);
	printf("%s", line);

	line = get_next_line(fd);
	printf("%s", line);
}