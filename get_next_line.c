/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchernyu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 12:49:09 by mchernyu          #+#    #+#             */
/*   Updated: 2021/11/16 15:12:10 by mchernyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_all(int fd, char *remainder);
char	*get_result(char *remainder);
char	*get_remainder(char *remainder);

char	*get_next_line(int fd)
{
	char		*result;
	static char	*remainder;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remainder = get_all(fd, remainder);
	if (!remainder)
		return (NULL);
	result = get_result(remainder);
	remainder = get_remainder(remainder);
	return (result);
}

char	*get_all(int fd, char *remainder)
{
	char	*buff;
	int		read_bytes;

	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (buff == NULL)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(remainder, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_bytes] = '\0';
		remainder = ft_strjoin(remainder, buff);
	}
	free(buff);
	return (remainder);
}

char	*get_result(char *remainder)
{
	int	i;
	char	*tmp;

	i = 0;
	if (!remainder[i])
		return (NULL);
	while(remainder[i] != '\0' && remainder[i] != '\n')
		i++;
	tmp = (char *)malloc(i + 2);
	if (!tmp)
		return (NULL);
	i = 0;
	while (remainder[i] != '\0' && remainder[i] != '\n')
	{
		tmp[i] = remainder[i];
		i++;
	}
	if (remainder[i] == '\n')
	{
		tmp[i] = remainder[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*get_remainder(char *remainder)
{
	int	i;
	int	j;
	char	*tmp;

	i = 0;
	j = 0;
	while(remainder[i] != '\0' && remainder[i] != '\n')
		i++;
	if(!remainder[i])
	{
		free(remainder);
		return (NULL);
	}
	tmp = (char *)malloc(ft_strlen(remainder) - i + 1);
	if (tmp == NULL)
		return (NULL);
	i++;
	j = 0;
	while(remainder[i] != '\0')
	{
		tmp[j] = remainder[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	free(remainder);
	return (tmp);
}
