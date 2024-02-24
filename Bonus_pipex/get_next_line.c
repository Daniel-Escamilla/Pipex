/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 14:40:35 by descamil          #+#    #+#             */
/*   Updated: 2023/12/07 13:08:13 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_l(int fd, char *buffer)
{
	char	aux[BUFFER_SIZE + 1];
	int		bytes_read;

	while (1)
	{
		if (buffer && buffer[0] == '\0')
			buffer = NULL;
		bytes_read = read(fd, aux, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		aux[bytes_read] = '\0';
		if (aux[0] == '\0')
			return (buffer);
		buffer = ft_strjoin(buffer, aux);
		if (!buffer)
			return (NULL);
		if (bytes_read != BUFFER_SIZE || ft_strchr(buffer, '\n'))
			return (buffer);
	}
	return (NULL);
}

char	*extraer_linea(char *buffer)
{
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_calloc(i + 1, 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*delete_line(char *buffer)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	i++;
	new = ft_calloc(ft_strlen(buffer) - i + 1, 1);
	if (!new)
		return (NULL);
	j = 0;
	while (buffer[i])
		new[j++] = buffer[i++];
	free(buffer);
	buffer = NULL;
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0)
		return (NULL);
	buffer = read_l(fd, buffer);
	line = extraer_linea(buffer);
	buffer = delete_line(buffer);
	if ((buffer && buffer[0] == '\0') || !buffer)
	{
		free(buffer);
		buffer = NULL;
	}
	if ((line && line[0] == '\0' ) || !line)
	{
		free(line);
		line = NULL;
	}
	return (line);
}

// void runleaks(void)
// {
//    system("leaks a.out");
// }

// int	main(void)
// {
// 	char	*line;
// 	int		fd;
// 	int		i;

// 	i = 1;
// 	fd = open("read_error.txt", O_RDONLY);
// 	if (fd == -1)
// 		return (1);
// 	while (i > 0)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		free(line);
// 		i--;
// 	}
// 	// atexit(runleaks);
// 	close (fd);
// 	return (0);
// }
