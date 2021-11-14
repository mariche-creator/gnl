/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariche <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 21:36:29 by mariche           #+#    #+#             */
/*   Updated: 2021/11/03 21:40:59 by mariche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"


int main(void)
{
    int fd;
    char *line;

    fd = open("test.txt", O_RDONLY);
    line = get_next_line(fd);
    printf("%s", line);

    line = get_next_line(fd);                                                                                                                                                   printf("%s", line);

    line = get_next_line(fd);                                                                                                                                                   printf("%s", line);

    line = get_next_line(fd);                                                                                                                                                   printf("%s", line);

    line = get_next_line(fd);                                                                                                                                                   printf("%s", line);
}
