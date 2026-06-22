/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maazizog <maazizog@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 20:02:49 by maazizog          #+#    #+#             */
/*   Updated: 2026/06/22 22:18:42 by maazizog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read_and_save(int fd, char *saved)
{
	int		bytes;
	char	*buffer;
	char	*tmp;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(saved), saved = NULL, NULL);
	bytes = 1;
	while (!ft_find_newline(saved) && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (free(buffer), free(saved), NULL);
		buffer[bytes] = '\0';
		if (bytes > 0)
		{
			tmp = ft_strjoin(saved, buffer);
			free(saved);
			saved = NULL;
			saved = tmp;
			if (!saved)
				return (free(buffer), buffer = NULL, NULL);
		}
	}
	return (free(buffer), buffer = NULL, saved);
}

static char	*ft_extract_line(char *saved)
{
	int		i;
	char	*line;
	int		len;

	if (!saved || !saved[0])
		return (NULL);
	len = ft_line_len(saved);
	line = malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = saved[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*line;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(saved);
		saved = NULL;
		return (NULL);
	}
	saved = ft_read_and_save(fd, saved);
	if (!saved)
		return (NULL);
	line = ft_extract_line(saved);
	if (line == NULL)
	{
		free(saved);
		saved = NULL;
		return (NULL);
	}
	tmp = ft_save_remainder(saved);
	free(saved);
	saved = tmp;
	return (line);
}

/*int	main(void)
{
	int		fd;
	char	*line;
	int		line_count;

	fd = open("./test.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Error: Could not open test.txt\n");
		return (1);
	}
	line_count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line)
		{
			line_count++;
			printf("Line %d: %s", line_count, line);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	printf("\nTotal lines read: %d\n\n", line_count);
	return (0);
}
*/