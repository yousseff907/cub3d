/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:20:29 by yitani            #+#    #+#             */
/*   Updated: 2025/08/14 19:37:37 by yitani           ###   ########.fr       */
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

void	store_map(char **parsed_file, int start_index, t_cub3d *cub)
{
	int	map_lines;
	int	i;

	map_lines = size_of_arr(parsed_file) - start_index;
	i = 0;
	cub->map.grid = malloc((map_lines + 1) * sizeof(char *));
	if (!cub->map.grid)
	{
		ft_putendl_fd("Error: Memory allocation failed", 2);
		return (free_split(parsed_file), exit(1));
	}
	while (start_index < size_of_arr(parsed_file))
	{
		cub->map.grid[i] = ft_strdup(parsed_file[start_index]);
		if (!cub->map.grid[i])
		{
			ft_putendl_fd("Error: Memory allocation failed", 2);
			return (free_split(parsed_file), cleanup_cub3d(cub), exit(1));
		}
		start_index++;
		i++;
	}
	cub->map.grid[i] = NULL;
	cub->map.height = map_lines;
	cub->map.width = calculate_map_width(cub->map.grid);
}
