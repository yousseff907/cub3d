/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 08:09:48 by odana             #+#    #+#             */
/*   Updated: 2025/08/20 16:13:25 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	draw_dot_line(t_graphics *gfx, t_minimap *minimap)
{
	int	distance_sq;
	int	j;

	j = -minimap->dot_size;
	while (j <= minimap->dot_size)
	{
		distance_sq = minimap->offset_x * minimap->offset_x + j * j;
		if (distance_sq <= minimap->dot_size * minimap->dot_size)
		{
			minimap->color = 0xFF0000;
			minimap->pixel_x = minimap->center_x + minimap->offset_x;
			minimap->pixel_y = minimap->center_y + j;
			draw_minimap_pixel(gfx, minimap->pixel_x, minimap->pixel_y,
				minimap);
		}
		j++;
	}
}

static void	draw_player_dot(t_graphics *gfx, t_minimap *minimap)
{
	minimap->offset_x = -minimap->dot_size;
	while (minimap->offset_x <= minimap->dot_size)
	{
		draw_dot_line(gfx, minimap);
		minimap->offset_x++;
	}
}

void	draw_player_on_minimap(t_cub3d *cub)
{
	t_minimap	minimap;

	if (!is_player_in_bounds(cub))
		return ;
	minimap = init_minimap(cub);
	minimap.center_x = (int)(cub->cam.pos_x * minimap.scale);
	minimap.center_y = (int)(cub->cam.pos_y * minimap.scale);
	minimap.dot_size = get_player_dot_size(minimap.scale);
	draw_player_dot(&cub->gfx, &minimap);
}
