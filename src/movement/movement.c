/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:53:09 by odana             #+#    #+#             */
/*   Updated: 2025/08/20 16:17:43 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	can_move_to(t_cub3d *cub, double new_x, double new_y)
{
	int		map_x;
	int		map_y;
	char	cell;
	t_door	*door;

	map_x = (int)new_x;
	map_y = (int)new_y;
	if (map_y < 0 || map_y >= cub->map.height || map_x < 0)
		return (0);
	if (map_x >= (int)ft_strlen(cub->map.grid[map_y]))
		return (0);
	cell = cub->map.grid[map_y][map_x];
	if (cell == '1')
		return (0);
	if (is_space(cell))
		return (0);
	if (cell == 'D')
	{
		door = find_door(cub, map_x, map_y);
		if (door)
			return (can_pass(cub, map_x, map_y));
		return (0);
	}
	return (1);
}

void	move_forward(t_cub3d *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->cam.pos_x + cub->cam.dir_x * cub->cam.move_speed;
	new_y = cub->cam.pos_y + cub->cam.dir_y * cub->cam.move_speed;
	if (can_move_to(cub, cub->cam.pos_x, new_y))
		cub->cam.pos_y = new_y;
	if (can_move_to(cub, new_x, cub->cam.pos_y))
		cub->cam.pos_x = new_x;
}

void	move_backward(t_cub3d *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->cam.pos_x - cub->cam.dir_x * cub->cam.move_speed;
	new_y = cub->cam.pos_y - cub->cam.dir_y * cub->cam.move_speed;
	if (can_move_to(cub, cub->cam.pos_x, new_y))
		cub->cam.pos_y = new_y;
	if (can_move_to(cub, new_x, cub->cam.pos_y))
		cub->cam.pos_x = new_x;
}

void	move_left(t_cub3d *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->cam.pos_x - cub->cam.plane_x * cub->cam.move_speed;
	new_y = cub->cam.pos_y - cub->cam.plane_y * cub->cam.move_speed;
	if (can_move_to(cub, cub->cam.pos_x, new_y))
		cub->cam.pos_y = new_y;
	if (can_move_to(cub, new_x, cub->cam.pos_y))
		cub->cam.pos_x = new_x;
}

void	move_right(t_cub3d *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->cam.pos_x + cub->cam.plane_x * cub->cam.move_speed;
	new_y = cub->cam.pos_y + cub->cam.plane_y * cub->cam.move_speed;
	if (can_move_to(cub, cub->cam.pos_x, new_y))
		cub->cam.pos_y = new_y;
	if (can_move_to(cub, new_x, cub->cam.pos_y))
		cub->cam.pos_x = new_x;
}
