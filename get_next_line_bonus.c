/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 20:47:50 by aylaaouf          #+#    #+#             */
/*   Updated: 2024/12/15 23:03:25 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_buffer(int fd, char *buffer)
{
	char	*temp_buffer;
	int		bytes_read;

	temp_buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!temp_buffer)
		return (free(buffer), NULL);
	bytes_read = 1;
	while (!ft_strchr(buffer, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(temp_buffer);
			return (NULL);
		}
		temp_buffer[bytes_read] = '\0';
		buffer = ft_strjoin(buffer, temp_buffer);
		if (!buffer)
		{
			free(temp_buffer);
			return (NULL);
		}
	}
	free(temp_buffer);
	return (buffer);
}

static char	*get_line(char *buffer)
{
	char	*line;
	char	*new_line_pos;
	size_t	len;
	size_t	i;

	if (!buffer || !*buffer)
		return (NULL);
	new_line_pos = ft_strchr(buffer, '\n');
	if (new_line_pos)
		len = new_line_pos - buffer + 1;
	else
		len = ft_strlen(buffer);
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (free(line), NULL);
	i = 0;
	while (i < len)
	{
		line[i] = buffer[i];
		i++;
	}
	line[len] = '\0';
	return (line);
}

static char	*update_buffer(char *buffer)
{
	char	*new_buffer;
	char	*new_line_pos;

	new_line_pos = ft_strchr(buffer, '\n');
	if (!new_line_pos)
		return (NULL);
	new_buffer = ft_strdup(new_line_pos + 1);
	if (!new_buffer)
		return (NULL);
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1337];
	char		*line;
	char		*new_buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = read_buffer(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = get_line(buffer[fd]);
	if (!line)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	new_buffer = update_buffer(buffer[fd]);
	if (!new_buffer)
	{
		return (NULL);
		buffer[fd] = NULL;
	}
	else
		buffer[fd] = new_buffer;
	return (line);
}
