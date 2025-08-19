/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 00:31:06 by odana             #+#    #+#             */
/*   Updated: 2025/08/20 00:31:42 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static t_wall_draw	init_door_wall_draw(t_ray *ray, int screen_x)
{
	t_wall_draw	wall;

	wall.line_height = (int)(HEIGHT / ray->wall_dist);
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

static void	draw_door_texture_column(t_graphics *gfx, t_wall_draw *wall, 
				char *tex_data, int tex_x)
{
	int		y;
	int		tex_y;
	int		color;
	double	tex_pos;

	tex_pos = (wall->draw_start - HEIGHT / 2 + wall->line_height / 2) 
		* wall->step;
	y = wall->draw_start;
	while (y < wall->draw_end)
	{
		tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += wall->step;
		color = get_pixel_texture(tex_data, tex_x, tex_y, wall->line_length);
		put_pixel(gfx, wall->screen_x, y, color);
		y++;
	}
}

static void	draw_door_background(t_graphics *gfx, t_wall_draw *wall, 
				t_textures *txt)
{
	draw_ceiling(gfx, wall->screen_x, wall->draw_start, txt->ceiling_color);
	draw_floor(gfx, wall->screen_x, wall->draw_end, txt->floor_color);
}

void	draw_door_column(t_graphics *gfx, int screen_x, t_ray *ray, 
			t_door *door, t_textures *txt)
{
	t_wall_draw	wall;
	char		*tex_data;
	int			tex_x;

	tex_x = calculate_door_tex_x(door, ray);
	if (tex_x < 0)
		return ;
	wall = init_door_wall_draw(ray, screen_x);
	tex_data = get_door_wall_texture(ray, txt, &wall.line_length);
	draw_door_background(gfx, &wall, txt);
	draw_door_texture_column(gfx, &wall, tex_data, tex_x);
}
