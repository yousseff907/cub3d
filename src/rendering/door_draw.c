/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 00:31:06 by odana             #+#    #+#             */
/*   Updated: 2025/08/20 16:25:42 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static t_wall_draw	init_door_draw(t_ray *ray)
{
	t_wall_draw	wall;

	wall.line_height = (int)(HEIGHT / ray->wall_dist);
	wall.draw_start = (-wall.line_height / 2) + (HEIGHT / 2);
	wall.draw_end = (wall.line_height / 2) + (HEIGHT / 2);
	wall.step = 1.0 * TEX_HEIGHT / wall.line_height;
	if (wall.draw_start < 0)
		wall.draw_start = 0;
	if (wall.draw_end >= HEIGHT)
		wall.draw_end = HEIGHT - 1;
	return (wall);
}

static void	draw_door_texture(t_cub3d *cub, t_wall_draw wall, int tex_x)
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
		color = get_pixel_texture(cub->txt.door_data, tex_x, tex_y,
				cub->txt.door_length);
		put_pixel(&cub->gfx, wall.screen_x, y, color);
		y++;
	}
}

static void	draw_transparent_area(t_cub3d *cub, int screen_x,
		int start, int end)
{
	int	y;
	int	bg_color;

	bg_color = 0x202020;
	y = start;
	while (y < end)
	{
		put_pixel(&cub->gfx, screen_x, y, bg_color);
		y++;
	}
}

void	draw_door_column(t_cub3d *cub, int screen_x, t_ray *ray, t_door *door)
{
	t_wall_draw	wall;
	int			tex_x;
	int			door_end;

	wall = init_door_draw(ray);
	wall.screen_x = screen_x;
	tex_x = calculate_texture(ray);
	door_end = wall.draw_start + (int)(wall.line_height
			* (1.0 - door->open_progress));
	if (door_end > wall.draw_end)
		door_end = wall.draw_end;
	draw_ceiling(&cub->gfx, screen_x, wall.draw_start, cub->txt.ceiling_color);
	if (door->open_progress < 1.0 && door_end > wall.draw_start)
	{
		wall.draw_end = door_end;
		draw_door_texture(cub, wall, tex_x);
	}
	if (door->open_progress > 0.0 && door_end < wall.draw_end)
		draw_transparent_area(cub, screen_x, door_end, wall.draw_end);
	draw_floor(&cub->gfx, screen_x, wall.draw_end, cub->txt.floor_color);
}
