/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvicol <cvicol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:54:04 by cvicol            #+#    #+#             */
/*   Updated: 2024/05/31 17:32:38 by cvicol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (!dst && !src)
		return (dst);
	if (src < dst)
		while (n--)
			d[n] = s[n];
	else
		while (n--)
			*d++ = *s++;
	return (dst);
}

char	*ft_strdup(const char *s)
{
	char	*s1;
	int		i;

	i = 0;
	while (s[i] != '\0')
		i++;
	s1 = malloc(sizeof(char) * (i + 1));
	if (!s1)
		return (NULL);
	s1[i] = '\0';
	i = i - 1;
	while (i >= 0 && s[i])
	{
		s1[i] = s[i];
		i = i - 1;
	}
	return (s1);
}

char	*ft_strchr(const char *s, int c)
{
	int	posocc;

	posocc = 0;
	while (s[posocc] != '\0')
	{
		if (s[posocc] == (char)c)
		{
			return ((char *)s + posocc);
		}
		++posocc;
	}
	if (s[posocc] == (char)c)
		return ((char *)s + posocc);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		lens1;
	int		lens2;

	lens1 = 0;
	lens2 = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	while (s1[lens1] != '\0')
		lens1++;
	while (s2[lens2] != '\0')
		lens2++;
	str = malloc (sizeof(char) * (lens1 + lens2 + 1));
	if (!str)
		return (NULL);
	ft_memmove(str, s1, lens1);
	ft_memmove(str + lens1, s2, lens2);
	str[lens1 + lens2] = '\0';
	return (str);
}

char	*read_from_file(int fd)
{
	char	*buff;
	int		n;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	n = read(fd, buff, BUFFER_SIZE);
	if (n <= 0)
	{
		free(buff);
		buff = NULL;
		return (NULL);
	}
	if (read(fd, 0, 0) < 0)
	{
		free (buff);
		buff = NULL;
	}
	buff[n] = '\0';
	return (buff);
}
