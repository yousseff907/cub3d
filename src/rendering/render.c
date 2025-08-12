/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:58:53 by odana             #+#    #+#             */
/*   Updated: 2025/08/12 17:31:55 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_ray	cast_ray(t_camera *cam, t_map *map, int screen_x)
{
	t_ray	ray;
	double camera_x;

	camera_x = 2.0 * screen_x / WIDTH - 1.0;
	ray.pos_x = cam->pos_x;
	ray.pos_y = cam->pos_y;
	ray.dir_x = cam->dir_x + cam->plane_x * camera_x;
	ray.dir_y = cam->dir_y + cam->plane_y * camera_x;
	ray.wall_dist = dda(&ray, map);
	return (ray);
}

void	*wall_tex(t_ray *ray, t_textures *tex)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (tex->east);
		else
			return (tex->west);
	}
	else
	{
		if (ray->dir_y > 0)
			return (tex->south);
		else
			return (tex->north);
	}
}

int	tex_coord(t_ray *ray)
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
		|| (ray->side == 1 && ray->dir_y < 0))
		tex_x = TEX_WIDTH - tex_x - 1;
	return (tex_x);
}

void	draw_wall_column(t_graphics *gfx, int x, t_ray *ray, t_textures *txt)
{
	int	line_height;
	int	draw_start;
	int	draw_end;

	line_height = (int)(HEIGHT / ray->wall_dist);
	draw_start = (HEIGHT - line_height) / 2;
	draw_end = (HEIGHT + line_height) / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	draw_ceiling(gfx, x, draw_start, txt->ceiling_color);
	draw_wall(gfx, x, ray, wall_tex(ray, txt), tex_coord(ray));
	draw_floor(gfx, x, draw_end, txt->floor_color);
}

void	render_frame(t_cub3d *cub)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIDTH)
	{
		ray = cast_ray(&cub->cam, &cub->map, x);
		draw_wall_column(&cub->gfx, x, &ray, &cub->txt);
		x++;
	}
	mlx_put_image_to_window(cub->gfx.mlx_ptr, cub->gfx.win_ptr, cub->gfx.img_ptr, 0, 0);
}
