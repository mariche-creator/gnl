/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_get_next_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchernyu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:55:12 by mchernyu          #+#    #+#             */
/*   Updated: 2021/11/14 17:52:21 by mchernyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "get_next_line.h"

char    *first_line(int fd, int *flag, char *buff, char *remainder);
char    *other_lines(int fd, char *buff, char *result, char *remainder);

char    *get_next_line(int fd)
{
    char    *result;
    char    buff;
    static char *remainder;
    
    //if (flag != 1)
	//	flag = 0;
    result = NULL;
	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (buff == NULL)
		return (NULL);
	printf("Flag at main is %d", flag);
    if(flag == 0)
		result = first_line(fd, &flag, buff, remainder);
    else
        result = other_lines(fd, buff, result, remainder);
    return (result);
}

char    *first_line(int fd, int *flag, char *buff, char *remainder)
{
	ssize_t bytes;
    char *result;
    int i;
    int j;

   	printf("Flag at first line is %d\n", *flag);
	i = 0;
    j = 0;
    *flag = 1;
	printf("Flag after assigning is %d\n", *flag);
    bytes = read(fd, buff, BUFFER_SIZE);
    if(bytes >= 0)
    {
        result = (char *)malloc(bytes + 1);
        while((buff[i] != '\n' || buff[i] != '\0') && bytes > 0)
        { 
			result[i] = buff[i];
            i++;
            bytes--;
        }
        if(buff[i] == '\n')
        {
            result[i] = '\n';
            i++;
            while (bytes > 0)
            {
                remainder[j] = buff[i];
                j++;
                i++;
                bytes--;
            }
            remainder[j] = '\0';
        }
        result[i] = '\0';
		free(buff);
		return (result);
    }
    return (NULL);
}

char    *other_lines(int fd, char *buff, char *result, char *remainder)
{
    ssize_t bytes;
    char tmp;
    int i;
    int j;
   
    printf("Entered into other_lines");
	i = 0;
	j = 0;
	tmp = (char *)malloc(BUFFER_SIZE);
	if (tmp == NULL)
		return (NULL);
	bytes = read(fd, buff, BUFFER_SIZE);
    if(bytes >= 0)
    {
        while((buff[i] != '\n' || buff [i] != '\0') && bytes > 0)
        {
            tmp[i] = buff[i];
            i++;
            bytes--;
        }
        if(buff[i] == '\n')
        {
            tmp[i] = '\n';
            i = 0;
            while(bytes > 0)
            {
                remainder[j] = tmp[i];
                j++;
                i++;
                bytes--;
            }
            remainder[j] = '\0';      
        }
        tmp[i] = '\0';
    }
    buff = result;
    result = (char *)malloc((ft_strlen(result)) + 2);
	if (result == NULL)
		return (NULL);
    result = ft_strjoin(result, tmp);
    free(buff);
    return (result);
}
