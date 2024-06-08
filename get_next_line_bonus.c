/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvicol <cvicol@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 07:02:04 by cvicol            #+#    #+#             */
/*   Updated: 2024/06/08 07:06:08 by cvicol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*append_to_buffer(char *final, char *buff)
{
	char	*temp;

	temp = final;
	final = ft_strjoin(final, buff);
	free(temp);
	temp = NULL;
	return (final);
}

char	*initialize_final(char	**aux)
{
	if (*aux)
		return (ft_strdup(*aux));
	else
		return (ft_strdup(""));
}

char	*read_next_buf(int fd, char **aux)
{
	char	*final;
	int		read_bytes;
	char	*buff;

	final = initialize_final(aux);
	if (!final)
		return (free (*aux), *aux = NULL, NULL);
	read_bytes = 0;
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (ft_strchr(final, '\n') == NULL)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes < 0)
			return (free (final), final = NULL, free (*aux),
				*aux = NULL, free(buff), buff = NULL, NULL);
		if (read_bytes == 0)
			break ;
		buff[read_bytes] = '\0';
		final = append_to_buffer(final, buff);
		if (!*final)
			return (free (*aux), *aux = NULL, NULL);
	}
	return (free (buff), buff = NULL, free (*aux), *aux = NULL, final);
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
	static char	*buf[1024];
	char		*line;
	char		*newline_pos;
	char		*new_buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf[fd] = read_next_buf(fd, &buf[fd]);
	if (!buf[fd])
		return (NULL);
	if (!buf[fd][0])
		return (free(buf[fd]), buf[fd] = NULL, NULL);
	line = extract_line(buf[fd]);
	newline_pos = ft_strchr(buf[fd], '\n');
	if (newline_pos)
	{
		new_buff = ft_strdup(newline_pos + 1);
		free(buf[fd]);
		buf[fd] = NULL;
		buf[fd] = new_buff;
		return (line);
	}
	else
		return (free(buf[fd]), buf[fd] = (NULL), line);
}
