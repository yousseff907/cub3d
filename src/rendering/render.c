/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:58:53 by odana             #+#    #+#             */
/*   Updated: 2025/08/11 19:53:23 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_ray	cast_ray(t_camera *cam, t_map *map, int screen_x)
{
	t_ray	ray;
	double	wall_dist;
	double camera_x;

	camera_x = 2.0 * screen_x / WIDTH - 1.0;
	ray.pos_x = cam->pos_x;
	ray.pos_y = cam->pos_y;
	ray.dir_x = cam->dir_x + cam->plane_x * camera_x;
	ray.dir_y = cam->dir_y + cam->plane_y * camera_x;
	ray.wall_dist = dda(&ray, map);
	return (ray);
}

void	*wall_txt(t_ray *ray, t_textures *txt)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (txt->east);
		else
			return (txt->west);
	}
	else
	{
		if (ray->dir_y > 0)
			return (txt->south);
		else
			return (txt->north);
	}
}

int	txt_coord(t_ray *ray)
{
	double	wall_x;
	double	wall_hit;
	int		tex_x;

	wall_x = ray->pos_x + ray->wall_dist * ray->dir_x;
	if (ray->side == 0)
		wall_hit = ray->pos_y + ray->wall_dist * ray->dir_y;
	else
		wall_hit = wall_x;
	wall_hit = wall_hit - floor(wall_hit);
	tex_x = (int)(wall_hit * TEX_WIDTH);
	if ((ray->side == 0 && ray->dir_x > 0)
		||ray->side == 1 && ray->dir_y < 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	return (tex_x);
}
