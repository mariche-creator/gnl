/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchernyu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 12:49:09 by mchernyu          #+#    #+#             */
/*   Updated: 2021/11/01 21:38:08 by mchernyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strnew(size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char 	*ft_strcpy(char *dst, const char *src);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char 	*check_remainder(char *remainder, char **result);
void	ft_strclr(char *s);

char	*get_next_line(int fd)
{
	char buff[BUFFER_SIZE + 1];
	char *result;
	static char *remainder;
	char *tmp;
	int read_bytes;
	char *p_n;
	
	p_n = check_remainder(remainder, &result);
	while (!p_n && (read_bytes = read(fd, buff, BUFFER_SIZE)))
	{
		buff[read_bytes] = '\0';
		if ((p_n = ft_strchr(buff, '\n')))
		{
			if ((p_n = ft_strchr(buff, '\0')))
				remainder = ft_strdup(++p_n);
			*p_n = '\0';
			remainder = ft_strdup(++p_n);
		}
		tmp = result;
		result = ft_strjoin(result, buff);
		free(tmp);
	}
	return (result);
}

char *ft_strnew(size_t size)
{
	char *str;

	str = (char *)malloc(sizeof(char) * size + 1);
	if (str == NULL)
		return (NULL);
	str[size] = '\0';
	while (size)
	{	
		str[size] = '\0';
		size--;
	}
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (c == 0)
		return ((char *)(&s[i]));
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	char	*dst;

	dst = malloc(ft_strlen(s1) + 1);
	if (dst == NULL)
		return (NULL);
	ft_strcpy(dst, s1);
	return (dst);
}

char	*ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char *check_remainder(char *remainder, char **result)
{
	char *p_n;

	p_n = NULL;
	if (remainder)
	{
		if ((p_n = ft_strchr(remainder, '\n')))
		{
			*p_n = '\0';
			*result = ft_strdup(remainder);
			ft_strcpy(remainder, ++p_n);
		}
		else
		{
			*result = ft_strdup(remainder);
			ft_strclr(remainder);
		}
	}
	else
	{
		*result = ft_strnew(1);
	}
	return (p_n);
}

void	ft_strclr(char *s)
{
	if (s)
	{
		while (*s)
		{
			*s = '\0';
			s++;
		}
	}
}
