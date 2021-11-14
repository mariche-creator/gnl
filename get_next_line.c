/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariche <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:56:27 by mariche           #+#    #+#             */
/*   Updated: 2021/11/14 13:08:53 by mariche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *first_line(int fd, int *flag, char *buff, char *remainder);
char    *other_lines(int fd, char *buff, char *result, char *remainder);

char    *get_next_line(int fd)
{
    char    *result;
    char    buff[BUFFER_SIZE];
    static char *remainder;
    static int  flag;
    
    flag = 0;
    result = NULL;
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

    i = 0;
    j = 0;
    *flag = 1;
    bytes = read(fd, buff, BUFFER_SIZE);
    if(bytes >= 0) //>= 0 || > 0
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
    }
    return (result);
}

char    *other_lines(int fd, char *buff, char *result, char *remainder)
{
    ssize_t bytes;
    char tmp[BUFFER_SIZE];
    int i;
    int j;
   
    bytes = read(fd, buff, BUFFER_SIZE);
    if(bytes >= 0)
    {
        while((buff[i] != '\n' || buf [i] != '\0') && bytes > 0)
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
    result = ft_strjoin(result, tmp);
    free(buff);
    return (result);
}
