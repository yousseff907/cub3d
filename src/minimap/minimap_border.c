/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_border.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 02:14:31 by odana             #+#    #+#             */
/*   Updated: 2025/08/20 08:14:45 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	draw_border_horizontal(t_graphics *gfx, 
		t_minimap *minimap, int y)
{
	int	i;

	i = -1;
	while (i <= minimap->width)
	{
		draw_minimap_pixel(gfx, i, y, minimap);
		i++;
	}
}

static void	draw_border_vertical(t_graphics *gfx, 
		t_minimap *minimap, int x)
{
	int	i;

	i = -1;
	while (i <= minimap->height)
	{
		draw_minimap_pixel(gfx, x, i, minimap);
		i++;
	}
}

void	draw_minimap_border(t_graphics *gfx, t_minimap *minimap)
{
	draw_border_horizontal(gfx, minimap, -1);
	draw_border_horizontal(gfx, minimap, minimap->height);
	draw_border_vertical(gfx, minimap, -1);
	draw_border_vertical(gfx, minimap, minimap->width);
}

