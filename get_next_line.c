/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 02:46:59 by aylaaouf          #+#    #+#             */
/*   Updated: 2024/12/13 10:14:59 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_buffer(int fd, char *buffer)
{
	char	*temp_buffer;
	int		bytes_read;

	temp_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(temp_buffer);
		return (NULL);
	}
	temp_buffer[bytes_read] = '\0';
	if (!buffer)
		buffer = ft_strdup("");
	if (bytes_read == 0)
	{
		free(temp_buffer);
		return (buffer);
	}
	buffer = ft_strjoin(buffer, temp_buffer);
	free(temp_buffer);
	return (buffer);
}

char	*get_line(char *buffer)
{
	char	*line;
	char	*new_line_pos;
	size_t	len;
	size_t	i;

	new_line_pos = ft_strchr(buffer, '\n');
	if (new_line_pos)
		len = new_line_pos - buffer;
	else
		len = ft_strlen(buffer);
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = buffer[i];
		i++;
	}
	line[len] = '\0';
	return (line);
}

char	*update_buffer(char *buffer)
{
	char	*new_buffer;
	char	*new_line_pos;

	new_line_pos = ft_strchr(buffer, '\n');
	if (!new_line_pos)
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = ft_strdup(new_line_pos + 1);
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_line(buffer);
	buffer = update_buffer(buffer);
	return (line);
}
