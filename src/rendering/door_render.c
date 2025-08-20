/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 00:23:03 by odana             #+#    #+#             */
/*   Updated: 2025/08/20 16:25:58 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static double	get_door_wall_hit(t_ray *ray)
{
	double	wall_hit;

	if (ray->side == 0)
		wall_hit = ray->pos_y + ray->wall_dist * ray->dir_y;
	else
		wall_hit = ray->pos_x + ray->wall_dist * ray->dir_x;
	wall_hit = wall_hit - floor(wall_hit);
	return (wall_hit);
}

static double	get_horizontal_door_hit(t_ray *ray, t_door *door)
{
	double	wall_hit;
	double	adjusted_hit;

	wall_hit = get_door_wall_hit(ray);
	if (ray->side == 1)
	{
		adjusted_hit = wall_hit - door->open_progress;
		if (adjusted_hit < 0.0)
			return (-1.0);
		return (adjusted_hit);
	}
	return (wall_hit);
}

static double	get_vertical_door_hit(t_ray *ray, t_door *door)
{
	double	wall_hit;
	double	adjusted_hit;

	wall_hit = get_door_wall_hit(ray);
	if (ray->side == 0)
	{
		adjusted_hit = wall_hit - door->open_progress;
		if (adjusted_hit < 0.0)
			return (-1.0);
		return (adjusted_hit);
	}
	return (wall_hit);
}

static int	apply_texture_flip(int tex_x, t_ray *ray)
{
	int	should_flip;

	should_flip = 0;
	if (ray->side == 0 && ray->dir_x > 0)
		should_flip = 1;
	if (ray->side == 1 && ray->dir_y < 0)
		should_flip = 1;
	if (should_flip)
		return (TEX_WIDTH - tex_x - 1);
	return (tex_x);
}

int	calculate_door_tex_x(t_door *door, t_ray *ray)
{
	double	adjusted_hit;
	int		tex_x;

	if (door->orientation == HORIZONTAL)
		adjusted_hit = get_horizontal_door_hit(ray, door);
	else
		adjusted_hit = get_vertical_door_hit(ray, door);
	if (adjusted_hit < 0.0)
		return (-1);
	tex_x = (int)(adjusted_hit * TEX_WIDTH);
	return (apply_texture_flip(tex_x, ray));
}
