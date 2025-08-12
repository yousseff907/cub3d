/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:19:44 by odana             #+#    #+#             */
/*   Updated: 2025/08/12 17:31:43 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	calculate_texture_x(t_ray *ray)
{
	double	wall_hit;
	int		tex_x;

	if (ray->side == 0)
		wall_hit = ray->pos_y + ray->wall_dist * ray->dir_y;
	else
		wall_hit = ray->pos_x + ray->wall_dist * ray->dir_x;
	wall_hit -= floor(wall_hit);
	tex_x = (int)(wall_hit * TEX_WIDTH);
	if (ray->side == 0 && ray->dir_x > 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	return (tex_x);
}

int	get_texture_pixel(char *tex_data, int tex_x, int tex_y)
{
	int	color;

	if (tex_x < 0 || tex_x >= TEX_WIDTH || tex_y < 0 || tex_y >= TEX_HEIGHT)
		return (0x000000);
	color = *(int*)(tex_data + (tex_y * TEX_WIDTH + tex_x) * 4);
	return (color);
}

void	draw_wall(t_graphics *gfx, int x, t_ray *ray, char *tex_data, int tex_x)
{
	int		y;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_y;
	int		color;
	double	step;
	double	tex_pos;

	line_height = (int)(HEIGHT / ray->wall_dist);
	draw_start = (-line_height / 2) + (HEIGHT / 2);
	draw_end = (line_height / 2) + (HEIGHT / 2);
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	step = 1.0 * TEX_HEIGHT / line_height;
	tex_pos = (draw_start - HEIGHT / 2 + line_height / 2) * step;
	y = draw_start;
	while (y < draw_end)
	{
		tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;
		color = get_texture_pixel(tex_data, tex_x, tex_y);
		if (ray->side == 1)
			color = (color >> 1) & 8355711;  // Darken horizontal walls
		put_pixel(gfx, x, y, color);
		y++;
	}
}