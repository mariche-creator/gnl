/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariche <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 21:45:57 by mariche           #+#    #+#             */
/*   Updated: 2021/11/04 01:03:19 by mariche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *ft_search(const char *s, int c, int *len)
{
    size_t i;

    i = 0;
    while(s[i] != '\0')
    {
        if ((unsigned char)s[i] == (unsigned char)c)
            *len = i;
            return ((char *)&s[i]);
        i++;
    }
    *len = i;
    if (c == 0)
        return ((char *)(&s[i]));
    return (NULL);
}

size_t ft_strlen(const char *s)
{
    size_t i;

    i = 0;
    while(s[i] != '\0')
        i++;
    return (i);
}

char *ft_strdup(const char *s1)
{
    char *dst;
    int i;

    i = 0;
    dst = malloc(ft_strlen(s1) + 1);
    if (dst == NULL)
        return (NULL);
    while (s1 != '\0')
    {
        dst[i] = s1[i];
        i++;
    }
    dst[i] = '\0';
    return (dst);
}
