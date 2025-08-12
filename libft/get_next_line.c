/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 00:17:13 by yitani            #+#    #+#             */
/*   Updated: 2025/06/19 03:39:28 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

static char	*read_until_newline(int fd, char *saved_data, char *temp_buffer)
{
	ssize_t		bytes_read;
	char		*temp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(saved_data);
			return (NULL);
		}
		else if (bytes_read == 0)
			break ;
		temp_buffer[bytes_read] = '\0';
		if (!saved_data)
			saved_data = ft_strdup("");
		temp = saved_data;
		saved_data = ft_strjoin(temp, temp_buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(temp_buffer, '\n'))
			break ;
	}
	return (saved_data);
}

static char	*extract_remaining_line(char *stash)
{
	char	*remaining_data;
	size_t	nl_i;

	nl_i = 0;
	while (stash[nl_i] != '\n' && stash[nl_i] != '\0')
		nl_i++;
	if (stash[nl_i] == '\0')
		return (NULL);
	remaining_data = ft_substr(stash, nl_i + 1, ft_strlen(stash) - (nl_i + 1));
	if (*remaining_data == '\0')
	{
		free(remaining_data);
		remaining_data = NULL;
	}
	stash[nl_i + 1] = '\0';
	return (remaining_data);
}

char	*get_next_line(int fd)
{
	static char	*saved_data;
	char		*line;
	char		*temp_buffer;

	temp_buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp_buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(saved_data);
		free(temp_buffer);
		saved_data = NULL;
		temp_buffer = NULL;
		return (NULL);
	}
	line = read_until_newline(fd, saved_data, temp_buffer);
	free(temp_buffer);
	temp_buffer = NULL;
	if (!line)
		return (NULL);
	saved_data = extract_remaining_line(line);
	return (line);
}
