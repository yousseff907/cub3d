/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 00:10:04 by odana             #+#    #+#             */
/*   Updated: 2025/08/20 16:20:42 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	is_valid_position(char **map, int x, int y, int height)
{
	if (y < 0 || y >= height || x < 0)
		return (0);
	if (x >= (int)ft_strlen(map[y]))
		return (0);
	return (1);
}

static int	door_orientation(char **map, int x, int y, int height)
{
	int	left_wall;
	int	right_wall;
	int	top_wall;
	int	bottom_wall;

	left_wall = 0;
	right_wall = 0;
	top_wall = 0;
	bottom_wall = 0;
	if (is_valid_position(map, x - 1, y, height) && map[y][x - 1] == '1')
		left_wall = 1;
	if (is_valid_position(map, x + 1, y, height) && map[y][x + 1] == '1')
		right_wall = 1;
	if (is_valid_position(map, x, y - 1, height) && map[y - 1][x] == '1')
		top_wall = 1;
	if (is_valid_position(map, x, y + 1, height) && map[y + 1][x] == '1')
		bottom_wall = 1;
	if (left_wall && right_wall)
		return (VERTICAL);
	if (top_wall && bottom_wall)
		return (HORIZONTAL);
	return (HORIZONTAL);
}

static void	init_door(t_door *door, int x, int y, int orientation)
{
	door->x = x;
	door->y = y;
	door->state = DOOR_CLOSED;
	door->open_progress = 0.0;
	door->orientation = orientation;
	door->frames_since_trigger = 0;
}

static void	create_doors(t_cub3d *cub)
{
	int	i;
	int	j;
	int	door_index;
	int	orientation;

	door_index = 0;
	i = 0;
	while (i < cub->map.height)
	{
		j = 0;
		while (cub->map.grid[i] && cub->map.grid[i][j])
		{
			if (cub->map.grid[i][j] == 'D')
			{
				orientation = door_orientation(cub->map.grid, j, i,
						cub->map.height);
				init_door(&cub->door_mgr.doors[door_index], j, i, orientation);
				door_index++;
			}
			j++;
		}
		i++;
	}
}

void	init_door_system(t_cub3d *cub)
{
	cub->door_mgr.door_count = count_doors(cub);
	if (cub->door_mgr.door_count == 0)
	{
		cub->door_mgr.doors = NULL;
		return ;
	}
	cub->door_mgr.doors = malloc(sizeof(t_door) * cub->door_mgr.door_count);
	if (!cub->door_mgr.doors)
		cleanup_exit(cub, "Error: Failed to allocate memory for doors", 1);
	create_doors(cub);
}
