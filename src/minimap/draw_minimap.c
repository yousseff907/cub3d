/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 08:08:42 by odana             #+#    #+#             */
/*   Updated: 2025/08/20 08:08:55 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	draw_minimap_pixel(t_graphics *gfx, int x, int y, t_minimap *minimap)
{
	int	screen_x;
	int	screen_y;

	screen_x = minimap->margin + x;
	screen_y = minimap->margin + y;
	if (screen_x >= 0 && screen_x < WIDTH)
	{
		if (screen_y >= 0 && screen_y < HEIGHT)
			put_pixel(gfx, screen_x, screen_y, minimap->color);
	}
}

static void	draw_square_line(t_graphics *gfx, t_minimap *minimap)
{
	int	i;

	i = 0;
	while (i < minimap->scale)
	{
		draw_minimap_pixel(gfx, minimap->pixel_x + i, minimap->pixel_y, minimap);
		i++;
	}
}

void	draw_minimap_square(t_graphics *gfx, t_minimap *minimap)
{
	int	j;

	minimap->pixel_x = minimap->map_x * minimap->scale;
	minimap->pixel_y = minimap->map_y * minimap->scale;
	j = 0;
	while (j < minimap->scale)
	{
		minimap->pixel_y = minimap->map_y * minimap->scale + j;
		draw_square_line(gfx, minimap);
		j++;
	}
}

static void	draw_map_cell(t_cub3d *cub, t_minimap *minimap)
{
	char	cell;
	int		row_length;

	row_length = ft_strlen(cub->map.grid[minimap->map_y]);
	if (minimap->map_x < row_length)
	{
		cell = cub->map.grid[minimap->map_y][minimap->map_x];
		minimap->color = get_cell_color(cell, cub, minimap->map_x, minimap->map_y);
	}
	else
		minimap->color = 0xFFFFFF;
	draw_minimap_square(&cub->gfx, minimap);
}

static void	draw_map_row(t_cub3d *cub, t_minimap *minimap)
{
	minimap->map_x = 0;
	while (minimap->map_x < cub->map.width)
	{
		draw_map_cell(cub, minimap);
		minimap->map_x++;
	}
}

void	draw_minimap(t_cub3d *cub)
{
	t_minimap	minimap;

	minimap = init_minimap(cub);
	draw_minimap_border(&cub->gfx, &minimap);
	minimap.map_y = 0;
	while (minimap.map_y < cub->map.height)
	{
		draw_map_row(cub, &minimap);
		minimap.map_y++;
	}
}
