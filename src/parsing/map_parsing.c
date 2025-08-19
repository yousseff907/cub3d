/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:20:29 by yitani            #+#    #+#             */
/*   Updated: 2025/08/20 01:29:29 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	calculate_map_width(char **grid)
{
	int	max;
	int	curr;
	int	i;

	i = 0;
	max = 0;
	curr = 0;
	while (grid[i])
	{
		curr = ft_strlen(grid[i]);
		if (curr > max)
			max = curr;
		i++;
	}
	return (max);
}


static void	convert_whitespace_to_walls(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (is_space(line[i]))
			line[i] = '1';
		i++;
	}
}

void	store_map(char **parsed_file, int start_index, t_cub3d *cub)
{
	int	map_lines;
	int	i;

	map_lines = size_of_arr(parsed_file) - start_index;
	i = 0;
	cub->map.grid = malloc((map_lines + 1) * sizeof(char *));
	if (!cub->map.grid)
	{
		free_split(parsed_file);
		cleanup_exit(cub, "Error: Memory allocation failed", 1);
	}
	while (start_index < size_of_arr(parsed_file))
	{
		cub->map.grid[i] = ft_strdup(parsed_file[start_index]);
		if (!cub->map.grid[i])
		{
			free_split(parsed_file);
			cleanup_exit(cub, "Error: Memory allocation failed", 1);
		}
		convert_whitespace_to_walls(cub->map.grid[i]);
		start_index++;
		i++;
	}
	cub->map.grid[i] = NULL;
	cub->map.height = map_lines;
	cub->map.width = calculate_map_width(cub->map.grid);
}
