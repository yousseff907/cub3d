/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:29:06 by odana             #+#    #+#             */
/*   Updated: 2025/08/20 01:58:22 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	init_dda(t_ray *ray)
{
	ray->delta_x = fabs(1.0 / ray->dir_x);
	ray->delta_y = fabs(1.0 / ray->dir_y);
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (ray->pos_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (ray->pos_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_y;
	}
}

static double	wall_dist(t_ray *ray)
{
	double	perp_wall_dist;

	if (ray->side == 0)
		perp_wall_dist = (ray->map_x - ray->pos_x + (1 - ray->step_x) / 2.0) / ray->dir_x;
	else
		perp_wall_dist = (ray->map_y - ray->pos_y + (1 - ray->step_y) / 2.0) / ray->dir_y;
	return (perp_wall_dist);
}

static int	ray_hit_wall(t_ray *ray, t_cub3d *cub)
{
	char	cell;
	t_door	*door;

	if (ray->map_y < 0 || ray->map_y >= cub->map.height || 
		ray->map_x < 0 || ray->map_x >= (int)ft_strlen(cub->map.grid[ray->map_y]))
		return (1);
	
	cell = cub->map.grid[ray->map_y][ray->map_x];
	if (cell == '1' || is_space(cell))
		return (1);
	if (cell == 'D')
	{
		door = find_door(cub, ray->map_x, ray->map_y);
		if (door && door->open_progress < DOOR_PASSABLE_THRESHOLD)
			return (1);
	}
	return (0);
}

double	dda(t_ray *ray, t_cub3d *cub)
{
	int	hit;

	init_dda(ray);
	hit = 0;
	while (!hit)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		hit = ray_hit_wall(ray, cub);
	}
	return (wall_dist(ray));
}

