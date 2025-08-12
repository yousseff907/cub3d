/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:21:19 by yitani            #+#    #+#             */
/*   Updated: 2025/08/13 01:40:52 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	is_cub_file(char *file_name)
{
	char	*cub;

	cub = ft_strrchr(file_name, '.');
	if (!cub || cub == file_name)
		return (0);
	return (ft_strcmp(cub, ".cub") == 0);
}

void	validate_input(int argc, char *argv[])
{
	int	fd;

	if (argc == 1 || argc > 2)
	{
		ft_putendl_fd("Usage: ./cub3d map.cub", 2);
		exit(1);
	}
	if (!is_cub_file(argv[1]))
	{
		ft_putendl_fd("Error : enter a .cub file", 2);
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("open failed: %s\n", strerror(errno));
		exit(1);
	}
	close(fd);
}

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

									/*
	row[0] rows count for loop
	row[1] total number of rows
									*/

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
	map	= alloc_file(file_name);
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

void	file_content_identification(int argc, char **argv)
{
	char	**parsed_file;

	validate_input(argc, argv);
	parsed_file = store_file(argv[1]);
	indentify_type(argv[1]);
}