/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reading.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:51:31 by yitani            #+#    #+#             */
/*   Updated: 2025/08/20 16:34:25 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	rows_count(char *file_name)
{
	int		fd;
	int		row;
	char	*line;

	row = 0;
	fd = open(file_name, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		row++;
	}
	close(fd);
	return (row);
}

char	**alloc_file(char *file_name)
{
	char	**map;
	char	*line;
	int		row_col[3];
	int		fd;

	row_col[0] = 0;
	row_col[1] = rows_count(file_name);
	fd = open(file_name, O_RDONLY);
	map = malloc((row_col[1] + 1) * sizeof(char *));
	while (row_col[0] < row_col[1])
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		row_col[2] = ft_strlen(line);
		free(line);
		map[row_col[0]] = malloc((row_col[2] + 1) * sizeof(char));
		row_col[0]++;
	}
	close(fd);
	return (map);
}

char	**store_file(char *file_name)
{
	int		fd;
	char	*line;
	char	**map;
	int		row[2];

	row[1] = rows_count(file_name);
	row[0] = 0;
	map = alloc_file(file_name);
	fd = open(file_name, O_RDONLY);
	while (row[0] < row[1])
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		ft_strlcpy(map[row[0]], line, ft_strlen(line) + 1);
		free(line);
		row[0]++;
	}
	map[row[0]] = NULL;
	close(fd);
	return (map);
}
