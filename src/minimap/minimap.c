/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 08:03:29 by odana             #+#    #+#             */
/*   Updated: 2025/08/20 08:04:47 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	calculate_scale(t_cub3d *cub)
{
	int	available_width;
	int	available_height;
	int	scale_x;
	int	scale_y;

	available_width = WIDTH / 4;
	available_height = HEIGHT / 4;
	scale_x = available_width / cub->map.width;
	scale_y = available_height / cub->map.height;
	if (scale_x < scale_y)
		return (scale_x);
	return (scale_y);
}

static void	set_scale_limits(t_minimap *minimap)
{
	if (minimap->scale < 2)
		minimap->scale = 2;
	if (minimap->scale > 16)
		minimap->scale = 16;
}

static void	calculate_dimensions(t_minimap *minimap, t_cub3d *cub)
{
	minimap->width = cub->map.width * minimap->scale;
	minimap->height = cub->map.height * minimap->scale;
	if (minimap->width > minimap->height)
		minimap->max_size = minimap->width;
	else
		minimap->max_size = minimap->height;
}

static void	calculate_margin(t_minimap *minimap)
{
	minimap->margin = minimap->width / 10;
	if (minimap->margin < 10)
		minimap->margin = 10;
	if (minimap->margin > 30)
		minimap->margin = 30;
}

t_minimap	init_minimap(t_cub3d *cub)
{
	t_minimap	minimap;

	minimap.scale = calculate_scale(cub);
	set_scale_limits(&minimap);
	calculate_dimensions(&minimap, cub);
	calculate_margin(&minimap);
	return (minimap);
}
