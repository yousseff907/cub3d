/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:49:11 by odana             #+#    #+#             */
/*   Updated: 2025/08/12 21:04:50 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static t_wall_draw	init_wall_draw(double wall_dist, int screen_x)
{
	t_wall_draw	wall;

	wall.line_height = (int)(HEIGHT / wall_dist);
	wall.draw_start = (-wall.line_height / 2) + (HEIGHT / 2);
	wall.draw_end = (wall.line_height / 2) + (HEIGHT / 2);
	wall.step = 1.0 * TEX_HEIGHT / wall.line_height;
    wall.screen_x = screen_x;
	if (wall.draw_start < 0)
		wall.draw_start = 0;
	if (wall.draw_end >= HEIGHT)
		wall.draw_end = HEIGHT - 1;
	return (wall);
}

static void	draw_texture_column(t_graphics *gfx, t_wall_draw wall, 
			char *tex_data, int tex_x)
{
	int		y;
	int		tex_y; 
	int		color;
	double	tex_pos;

	tex_pos = (wall.draw_start - HEIGHT / 2 + wall.line_height / 2) * wall.step;
	
	y = wall.draw_start;
	while (y < wall.draw_end)
	{
		tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += wall.step;
		color = get_pixel_texture(tex_data, tex_x, tex_y);
		put_pixel(gfx, wall.screen_x, y, color);
		y++;
	}
}

void	draw_wall_column(t_graphics *gfx, int screen_x, t_ray *ray, t_textures *txt)
{
	t_wall_draw	wall;
	char		*tex_data;
	int			tex_x;

	wall = init_wall_draw(ray->wall_dist, screen_x);
	tex_data = get_wall_data(ray, txt);
	tex_x = calculate_texture(ray);
	draw_ceiling(gfx, screen_x, wall.draw_start, txt->ceiling_color);
	draw_texture_column(gfx, wall, tex_data,tex_x);
	draw_floor(gfx, screen_x, wall.draw_end, txt->floor_color);
}