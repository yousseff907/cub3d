/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:16:43 by yitani            #+#    #+#             */
/*   Updated: 2025/08/20 16:16:55 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
