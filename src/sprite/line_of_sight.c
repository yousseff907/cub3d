/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_of_sight.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:13:34 by odana             #+#    #+#             */
/*   Updated: 2025/08/20 16:12:13 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	is_wall_cell(t_cub3d *cub, int x, int y)
{
	if (y < 0 || y >= cub->map.height || x < 0)
		return (1);
	if (x >= (int)ft_strlen(cub->map.grid[y]))
		return (1);
	if (cub->map.grid[y][x] == '1' || is_space(cub->map.grid[y][x]))
		return (1);
	return (0);
}

static int	check_wall_collision(t_cub3d *cub, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	return (is_wall_cell(cub, map_x, map_y));
}

int	has_line_of_sight(t_cub3d *cub, double sprite_x, double sprite_y)
{
	double	distance;
	double	current_x;
	double	current_y;
	int		steps;
	int		i;

	distance = sqrt(pow(sprite_x - cub->cam.pos_x, 2)
			+ pow(sprite_y - cub->cam.pos_y, 2));
	steps = (int)(distance / 0.1);
	if (steps == 0)
		return (1);
	i = 1;
	while (i < steps)
	{
		current_x = cub->cam.pos_x + ((sprite_x - cub->cam.pos_x) * i / steps);
		current_y = cub->cam.pos_y + ((sprite_y - cub->cam.pos_y) * i / steps);
		if (check_wall_collision(cub, current_x, current_y))
			return (0);
		i++;
	}
	return (1);
}
