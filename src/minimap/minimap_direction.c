/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_direction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 08:10:12 by odana             #+#    #+#             */
/*   Updated: 2025/08/20 08:10:25 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	calculate_line_params(t_cub3d *cub, t_minimap *minimap)
{
	int	dir_len;

	dir_len = get_direction_length(minimap->scale);
	minimap->end_x = minimap->start_x + (int)(cub->cam.dir_x * dir_len);
	minimap->end_y = minimap->start_y + (int)(cub->cam.dir_y * dir_len);
	if (abs(minimap->end_x - minimap->start_x) > abs(minimap->end_y - minimap->start_y))
		minimap->steps = abs(minimap->end_x - minimap->start_x);
	else
		minimap->steps = abs(minimap->end_y - minimap->start_y);
}

static void	draw_line_pixels(t_graphics *gfx, t_minimap *minimap)
{
	double	step_x;
	double	step_y;
	int		i;

	if (minimap->steps <= 0)
		return ;
	step_x = (double)(minimap->end_x - minimap->start_x) / minimap->steps;
	step_y = (double)(minimap->end_y - minimap->start_y) / minimap->steps;
	i = 0;
	while (i <= minimap->steps)
	{
		minimap->pixel_x = minimap->start_x + (int)(i * step_x);
		minimap->pixel_y = minimap->start_y + (int)(i * step_y);
		if (minimap->pixel_x >= 0 && minimap->pixel_x < minimap->width)
		{
			if (minimap->pixel_y >= 0 && minimap->pixel_y < minimap->height)
			{
				minimap->color = 0xFF0000;
				draw_minimap_pixel(gfx, minimap->pixel_x, minimap->pixel_y, minimap);
			}
		}
		i++;
	}
}

void	draw_player_direction(t_cub3d *cub)
{
	t_minimap	minimap;

	if (!is_player_in_bounds(cub))
		return ;
	minimap = init_minimap(cub);
	minimap.start_x = (int)(cub->cam.pos_x * minimap.scale);
	minimap.start_y = (int)(cub->cam.pos_y * minimap.scale);
	calculate_line_params(cub, &minimap);
	draw_line_pixels(&cub->gfx, &minimap);
}
