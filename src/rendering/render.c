/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:58:53 by odana             #+#    #+#             */
/*   Updated: 2025/08/20 02:15:42 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_ray	cast_ray(t_camera *cam, t_cub3d *cub, int screen_x)
{
	t_ray	ray;
	double camera_x;

	camera_x = 2.0 * screen_x / WIDTH - 1.0;
	ray.pos_x = cam->pos_x;
	ray.pos_y = cam->pos_y;
	ray.dir_x = cam->dir_x + cam->plane_x * camera_x;
	ray.dir_y = cam->dir_y + cam->plane_y * camera_x;
	ray.wall_dist = dda(&ray, cub);
	return (ray);
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

void	render_frame(t_cub3d *cub)
{
	int		x;
	t_ray	ray;
	t_door	*door;

	if (!cub->gfx.img_ptr)
	{
		printf("ERROR: No image buffer allocated!\n");
		return;
	}
	x = 0;
	while (x < WIDTH)
	{
		ray = cast_ray(&cub->cam, cub, x);
		door = find_door(cub, ray.map_x, ray.map_y);
		if (door && door->open_progress < DOOR_PASSABLE_THRESHOLD)
			draw_door_column(cub, x, &ray, door);
		else
			draw_wall_column(&cub->gfx, x, &ray, &cub->txt);
		x++;
	}
	draw_minimap(cub);
	draw_player_on_minimap(cub);
	draw_player_direction(cub);
	mlx_put_image_to_window(cub->gfx.mlx_ptr, cub->gfx.win_ptr, cub->gfx.img_ptr, 0, 0);
}


