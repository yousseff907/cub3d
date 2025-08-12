/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:49:11 by odana             #+#    #+#             */
/*   Updated: 2025/08/12 16:49:46 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	draw_ceiling(t_graphics *gfx, int x, int end, int color)
{
	int	y;

	y = 0;
	while (y < end)
	{
		put_pixel(gfx, x, y, color);
		y++;
	}
}

void	draw_wall_segment(t_graphics *gfx, int x, int start, int end, int color)
{
	int	y;

	y = start;
	while (y < end)
	{
		put_pixel(gfx, x, y, color);
		y++;
	}
}

void	draw_floor(t_graphics *gfx, int x, int start, int color)
{
	int	y;

	y = start;
	while (y < HEIGHT)
	{
		put_pixel(gfx, x, y, color);
		y++;
	}
}

void	put_pixel(t_graphics *gfx, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = gfx->img_data + (y * gfx->line_length + x * (BITS_PER_PIXEL / 8));
		*(unsigned int*)dst = color;
	}
}