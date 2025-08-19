/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 00:18:29 by odana             #+#    #+#             */
/*   Updated: 2025/08/20 02:01:15 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	count_doors(t_cub3d *cub)
{
	int	i;
	int	j;
	int	door_count;

	door_count = 0;
	i = 0;
	while (i < cub->map.height)
	{
		j = 0;
		while (cub->map.grid[i] && cub->map.grid[i][j])
		{
			if (cub->map.grid[i][j] == 'D')
				door_count++;
			j++;
		}
		i++;
	}
	return (door_count);
}


t_door	*find_door(t_cub3d *cub, int x, int y)
{
	int	i;

	if (!cub->door_mgr.doors)
		return (NULL);
	i = 0;
	while (i < cub->door_mgr.door_count)
	{
		if (cub->door_mgr.doors[i].x == x && cub->door_mgr.doors[i].y == y)
			return (&cub->door_mgr.doors[i]);
		i++;
	}
	return (NULL);
}

int	can_pass(t_cub3d *cub, int x, int y)
{
	t_door	*door;

	door = find_door(cub, x, y);
	if (!door)
		return (0);
	return (door->open_progress > DOOR_PASSABLE_THRESHOLD);
}

int	block_movement(t_cub3d *cub, int x, int y)
{
	t_door	*door;

	door = find_door(cub, x, y);
	if (!door)
		return (1);
	return (door->open_progress <= DOOR_PASSABLE_THRESHOLD);
}

void	cleanup_doors(t_cub3d *cub)
{
	if (cub->door_mgr.doors)
	{
		free(cub->door_mgr.doors);
		cub->door_mgr.doors = NULL;
	}
	cub->door_mgr.door_count = 0;
}