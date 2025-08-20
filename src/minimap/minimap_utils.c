/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 07:58:07 by odana             #+#    #+#             */
/*   Updated: 2025/08/20 08:11:38 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	get_cell_color(char cell, t_cub3d *cub, int x, int y)
{
	t_door	*door;

	if (cell == '1')
		return (0xFFFFFF);
	if (cell == '0')
		return (0x333333);
	if (cell == 'D')
	{
		door = find_door(cub, x, y);
		if (door && door->open_progress > 0.5)
			return (0x00AA00);
		return (0x8B4513);
	}
	return (0x808080);
}

int	get_player_dot_size(int scale)
{
	int	dot_size;

	dot_size = scale / 3;
	if (dot_size < 2)
		dot_size = 2;
	if (dot_size > 5)
		dot_size = 5;
	return (dot_size);
}

int	get_direction_length(int scale)
{
	int	dir_len;

	dir_len = scale * 2;
	if (dir_len < 8)
		dir_len = 8;
	if (dir_len > 20)
		dir_len = 20;
	return (dir_len);
}

int	is_player_in_bounds(t_cub3d *cub)
{
	if (cub->cam.pos_x >= 0 && cub->cam.pos_x < cub->map.width)
	{
		if (cub->cam.pos_y >= 0 && cub->cam.pos_y < cub->map.height)
			return (1);
	}
	return (0);
}
