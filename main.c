#include "get_next_line.h"

int main()
{
    int fd = open("a.txt", O_RDONLY);
    if (fd == -1) {
        return 1;
    }
    char *a;
    while ((a = get_next_line(fd)) != NULL) {
        printf("next line: %s", a);
        free(a);
    }
    close(fd);
    return (0);
}


/*
char	*read_next_buf(int fd, char *aux)
{
	char	*buff;
	char	*final;
	int		n;
	char	*temp;

	buff = malloc(BUFFER_SIZE);
	if (!buff)
		return (NULL);
	final = aux ? ft_strdup(aux) : ft_strdup("");
	if (!final)
	{
		free(buff);
		return (NULL);
	}
	while (ft_strchr(final, '\n') == NULL)
	{
		n = read(fd, buff, BUFFER_SIZE);
		if (n <= 0)
		{
			free(buff);
			if (n == 0 && final[0] != '\0')
				return (final);
			free(final);
			return (NULL);
		}
		buff[n] = '\0';
		temp = final;
		final = ft_strjoin (final, buff);
		free(temp);
		if (!final)
		{
			free (buff);
			return (NULL);
		}
	}
	free (buff);
	free (aux);
	return (final);
}
*/
