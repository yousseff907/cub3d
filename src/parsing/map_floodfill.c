/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_floodfill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:44:11 by yitani            #+#    #+#             */
/*   Updated: 2025/08/20 16:35:24 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	is_position_visited(char **map, int x, int y, int height)
{
	if (y < 0 || y >= height || x < 0)
		return (1);
	if (x >= (int)ft_strlen(map[y]))
		return (1);
	return (map[y][x] == 'V');
}

int	flood_fill_escape_check(char **map, int x, int y, int height)
{
	char	current;

	if (y < 0 || y >= height || x < 0 || x >= (int)ft_strlen(map[y]))
		return (0);
	current = map[y][x];
	if (current == '1' || current == 'V')
		return (1);
	if (is_space(current))
	{
		map[y][x] = 'V';
		if (!flood_fill_escape_check(map, x + 1, y, height)
			|| !flood_fill_escape_check(map, x - 1, y, height)
			|| !flood_fill_escape_check(map, x, y + 1, height)
			|| !flood_fill_escape_check(map, x, y - 1, height))
			return (0);
		return (1);
	}
	map[y][x] = 'V';
	if (!flood_fill_escape_check(map, x + 1, y, height)
		|| !flood_fill_escape_check(map, x - 1, y, height)
		|| !flood_fill_escape_check(map, x, y + 1, height)
		|| !flood_fill_escape_check(map, x, y - 1, height))
		return (0);
	return (1);
}

int	validate_all_empty_positions(t_cub3d *cub)
{
	t_position	*empty_positions;
	t_position	*current;
	char		**map_copy;
	int			all_contained;

	empty_positions = find_all_empty_positions(cub);
	if (!empty_positions)
		return (1);
	all_contained = 1;
	current = empty_positions;
	while (current && all_contained)
	{
		map_copy = duplicate_map(cub);
		if (!map_copy)
		{
			free_position_list(empty_positions);
			return (0);
		}
		if (!flood_fill_escape_check(map_copy, current->x, current->y,
				cub->map.height))
			all_contained = 0;
		free_split(map_copy);
		current = current->next;
	}
	return (free_position_list(empty_positions), all_contained);
}

int	validate_map_flood_fill(t_cub3d *cub)
{
	return (validate_all_empty_positions(cub));
}

int	complete_map_validation(t_cub3d *cub)
{
	if (!validate_map_content(cub))
		return (0);
	if (!valid_player_count(cub))
	{
		ft_putendl_fd("Error: Map must have exactly one player", 2);
		return (0);
	}
	if (!validate_map_flood_fill(cub))
	{
		ft_putendl_fd("Error: Map has escape routes - not properly closed", 2);
		return (0);
	}
	return (1);
}
