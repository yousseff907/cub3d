/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 09:27:44 by odana             #+#    #+#             */
/*   Updated: 2025/08/20 09:27:45 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static t_sprite_draw	calculate_sprite_transform(t_sprite *sprite, 
	t_camera *cam)
{
	t_sprite_draw	draw;
	double			inv_det;

	draw.sprite_x = sprite->x - cam->pos_x;
	draw.sprite_y = sprite->y - cam->pos_y;
	inv_det = 1.0 / (cam->plane_x * cam->dir_y - cam->dir_x * cam->plane_y);
	draw.inv_det = inv_det;
	draw.transform_x = inv_det * (cam->dir_y * draw.sprite_x 
		- cam->dir_x * draw.sprite_y);
	draw.transform_y = inv_det * (-cam->plane_y * draw.sprite_x 
		+ cam->plane_x * draw.sprite_y);
	return (draw);
}

static void	calculate_sprite_screen_params(t_sprite_draw *draw)
{
	draw->sprite_screen_x = (int)((WIDTH / 2) * (1 + draw->transform_x 
		/ draw->transform_y));
	draw->sprite_height = abs((int)(HEIGHT / draw->transform_y));
	draw->sprite_width = abs((int)(HEIGHT / draw->transform_y));
	draw->draw_start_y = -draw->sprite_height / 2 + HEIGHT / 2;
	if (draw->draw_start_y < 0)
		draw->draw_start_y = 0;
	draw->draw_end_y = draw->sprite_height / 2 + HEIGHT / 2;
	if (draw->draw_end_y >= HEIGHT)
		draw->draw_end_y = HEIGHT - 1;
}

static void	calculate_sprite_x_bounds(t_sprite_draw *draw)
{
	draw->draw_start_x = -draw->sprite_width / 2 + draw->sprite_screen_x;
	if (draw->draw_start_x < 0)
		draw->draw_start_x = 0;
	draw->draw_end_x = draw->sprite_width / 2 + draw->sprite_screen_x;
	if (draw->draw_end_x >= WIDTH)
		draw->draw_end_x = WIDTH - 1;
}

static void	render_sprite_column(t_cub3d *cub, t_sprite_draw *draw,
	int stripe, int frame)
{
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;

	tex_x = (int)(256 * (stripe - (-draw->sprite_width / 2 
		+ draw->sprite_screen_x)) * TEX_WIDTH / draw->sprite_width) / 256;
	if (draw->transform_y > 0 && stripe > 0 && stripe < WIDTH 
		&& draw->transform_y < 1000)
	{
		y = draw->draw_start_y;
		while (y < draw->draw_end_y)
		{
			tex_y = (((y * 256 - HEIGHT * 128 + draw->sprite_height * 128) 
				* TEX_HEIGHT) / draw->sprite_height) / 256;
			color = get_pixel_texture(cub->txt.sprite_data[frame], 
				tex_x, tex_y, cub->txt.sprite_length[frame]);
			if ((color & 0x00FFFFFF) != 0)
				put_pixel(&cub->gfx, stripe, y, color);
			y++;
		}
	}
}

void	render_single_sprite(t_cub3d *cub, t_sprite *sprite)
{
	t_sprite_draw	draw;
	int				stripe;

	draw = calculate_sprite_transform(sprite, &cub->cam);
	calculate_sprite_screen_params(&draw);
	calculate_sprite_x_bounds(&draw);
	stripe = draw.draw_start_x;
	while (stripe < draw.draw_end_x)
	{
		render_sprite_column(cub, &draw, stripe, sprite->current_frame);
		stripe++;
	}
}