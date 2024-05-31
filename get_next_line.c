/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvicol <cvicol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:53:41 by cvicol            #+#    #+#             */
/*   Updated: 2024/05/31 17:32:17 by cvicol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

int	extra(char **final, char ***aux, int fd)
{
	char	*buff;

	buff = read_from_file(fd);
	if (!buff)
	{
		if (*final[0] != '\0')
		{
			free (**aux);
			**aux = NULL;
			return (1);
		}
		free(*final);
		*final = NULL;
		free (**aux);
		**aux = NULL;
		return (0);
	}
	*final = append_to_buffer(*final, buff);
	if (!*final)
	{
		free (**aux);
		**aux = NULL;
		return (0);
	}
	return (2);
}

char	*read_next_buf(int fd, char **aux)
{
	char	*final;

	if (*aux)
		final = ft_strdup(*aux);
	else
		final = ft_strdup("");
	if (!final)
	{
		free (*aux);
		*aux = NULL;
		return (NULL);
	}
	while (ft_strchr(final, '\n') == NULL)
	{
		if (extra(&final, &aux, fd) == 0)
			return (NULL);
		else
			return (final);
	}
	free (*aux);
	*aux = NULL;
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
	buf = read_next_buf(fd, &buf);
	if (!buf)
		return (NULL);
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
