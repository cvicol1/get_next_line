/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvicol <cvicol@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:53:41 by cvicol            #+#    #+#             */
/*   Updated: 2024/05/31 08:04:01 by cvicol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*append_to_buffer(char *final, char *buff)
{
	char	*temp;

	temp = final;
	final = ft_strjoin(final, buff);
	free(temp);
	temp = NULL;
	free(buff);
	buff = NULL;
	return (final);
}

char	*read_next_buf(int fd, char *aux)
{
	char	*buff;
	char	*final;

	if (aux)
		final = ft_strdup(aux);
	else
		final = ft_strdup("");
	if (!final)
	{
		free (aux);
		aux = NULL;
		return (NULL);
	}
	while (ft_strchr(final, '\n') == NULL)
	{
		buff = read_from_file(fd);
		if (!buff)
		{
			if (final[0] != '\0')
			{
				free (aux);
				aux = NULL;
				return (final);
			}
			free(final);
			final = NULL;
			free (aux);
			aux = NULL;
			return (NULL);
		}
		final = append_to_buffer(final, buff);
		if (!final)
		{
			free (aux);
			aux = NULL;
			return (NULL);
		}
	}
	free (aux);
	aux = NULL;
	return (final);
}

char	*extract_line(char *buf)
{
	char	*line;
	int		i;
	int		j;

	if (!buf)
		return (NULL);
	i = 0;
	j = 0;
	while (buf[i] != '\0' && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		line = malloc(i + 2);
	else
		line = malloc(i + 1);
	if (!line)
		return (NULL);
	while (j < i)
	{
		line[j] = buf[j];
		++j;
	}
	if (buf[i] == '\n')
		line[j++] = '\n';
	line[j] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*line;
	char		*newline_pos;
	char		*new_buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = read_next_buf(fd, buf);
	if (!buf)
		return (NULL);
	if (!buf[0])
	{
		free(buf);
		buf = NULL;
		return (NULL);
	}
	line = extract_line(buf);
	newline_pos = ft_strchr(buf, '\n');
	if (newline_pos)
	{
		new_buff = ft_strdup(newline_pos + 1);
		free(buf);
		buf = NULL;
		buf = new_buff;
	}
	else
	{
		free(buf);
		buf = (NULL);
	}
	return (line);
}
