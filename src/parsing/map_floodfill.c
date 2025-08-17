/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_floodfill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 19:27:14 by yitani            #+#    #+#             */
/*   Updated: 2025/08/17 19:35:04 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	find_player_position(t_cub3d *cub, int *player_x, int *player_y)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->map.height)
	{
		j = 0;
		while (cub->map.grid[i][j])
		{
			if (cub->map.grid[i][j] == 'N' || cub->map.grid[i][j] == 'S' ||
				cub->map.grid[i][j] == 'E' || cub->map.grid[i][j] == 'W')
			{
				*player_x = j;
				*player_y = i;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

char	**duplicate_map(t_cub3d *cub)
{
	char	**dup_map;
	int		i;

	dup_map = malloc(sizeof(char *) * (cub->map.height + 1));
	if (!dup_map)
		return (NULL);
	i = 0;
	while (i < cub->map.height)
	{
		dup_map[i] = ft_strdup(cub->map.grid[i]);
		if (!dup_map[i])
		{
			while (--i >= 0)
				free(dup_map[i]);
			free(dup_map);
			return (NULL);
		}
		i++;
	}
	dup_map[i] = NULL;
	return (dup_map);
}

int	flood_fill_escape_check(char **map, int x, int y, int height)
{
	if (y < 0 || y >= height)
		return (0);
	if (x < 0 || x >= (int)ft_strlen(map[y]))
		return (0);
	char current = map[y][x];
	if (current == '1')
		return (1);
	if (current == 'V')
		return (1);
	if (current == ' ')
		return (1);
	map[y][x] = 'V';
	if (!flood_fill_escape_check(map, x + 1, y, height) ||
		!flood_fill_escape_check(map, x - 1, y, height) ||
		!flood_fill_escape_check(map, x, y + 1, height) ||
		!flood_fill_escape_check(map, x, y - 1, height))
		return (0);
	return (1);
}

int	validate_map_flood_fill(t_cub3d *cub)
{
	char	**map_copy;
	int		player_x;
	int		player_y;
	int		result;

	find_player_position(cub, &player_x, &player_y);
	map_copy = duplicate_map(cub);
	if (!map_copy)
	{
		ft_putendl_fd("Error: Memory allocation failed", 2);
		return (0);
	}
	result = flood_fill_escape_check(map_copy, player_x, player_y, cub->map.height);
	free_split(map_copy);
	if (!result)
		ft_putendl_fd("Error: Map is not properly closed - player can escape", 2);
	return (result);
}

int	validate_player_not_on_edge(t_cub3d *cub)
{
	int	player_x;
	int	player_y;
	int	row_len;

	if (!find_player_position(cub, &player_x, &player_y))
		return (0);
	if (player_y == 0 || player_y == cub->map.height - 1)
	{
		ft_putendl_fd("Error: Player cannot be on map edge", 2);
		return (0);
	}
	row_len = ft_strlen(cub->map.grid[player_y]);
	if (player_x == 0 || player_x == row_len - 1)
	{
		ft_putendl_fd("Error: Player cannot be on map edge", 2);
		return (0);
	}
	return (1);
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
	if (!validate_player_not_on_edge(cub))
		return (0);
	if (!validate_map_flood_fill(cub))
		return (0);
	return (1);
}