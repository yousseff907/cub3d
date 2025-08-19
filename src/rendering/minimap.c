/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 02:14:31 by odana             #+#    #+#             */
/*   Updated: 2025/08/20 02:14:58 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	draw_minimap_pixel(t_graphics *gfx, int x, int y, int color)
{
	int	map_x;
	int	map_y;

	map_x = MINIMAP_MARGIN + x;
	map_y = MINIMAP_MARGIN + y;
	if (map_x >= 0 && map_x < WIDTH && map_y >= 0 && map_y < HEIGHT)
		put_pixel(gfx, map_x, map_y, color);
}

static void	draw_minimap_square(t_graphics *gfx, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_SCALE)
	{
		j = 0;
		while (j < MINIMAP_SCALE)
		{
			draw_minimap_pixel(gfx, x * MINIMAP_SCALE + i, 
				y * MINIMAP_SCALE + j, color);
			j++;
		}
		i++;
	}
}

static int	get_cell_color(char cell, t_cub3d *cub)
{
	t_door	*door;
	int		map_x;
	int		map_y;

	if (cell == '1')
		return (0xFFFFFF);
	if (cell == '0')
		return (0x000000);
	if (cell == 'D')
	{
		map_x = 0;
		map_y = 0;
		door = find_door(cub, map_x, map_y);
		if (door && door->open_progress > 0.5)
			return (0x00AA00);
		return (0x8B4513);
	}
	return (0x808080);
}

void	draw_minimap(t_cub3d *cub)
{
	int		x;
	int		y;
	int		color;
	char	cell;

	y = 0;
	while (y < cub->map.height && y * MINIMAP_SCALE < MINIMAP_SIZE)
	{
		x = 0;
		while (x < (int)ft_strlen(cub->map.grid[y]) && 
			x * MINIMAP_SCALE < MINIMAP_SIZE)
		{
			cell = cub->map.grid[y][x];
			color = get_cell_color(cell, cub);
			draw_minimap_square(&cub->gfx, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_player_on_minimap(t_cub3d *cub)
{
	int	player_x;
	int	player_y;
	int	i;
	int	j;

	player_x = (int)(cub->cam.pos_x * MINIMAP_SCALE);
	player_y = (int)(cub->cam.pos_y * MINIMAP_SCALE);
	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			draw_minimap_pixel(&cub->gfx, player_x + i, player_y + j, 0xFF0000);
			j++;
		}
		i++;
	}
}

void	draw_player_direction(t_cub3d *cub)
{
	int		player_x;
	int		player_y;
	int		end_x;
	int		end_y;
	double	dir_len;

	player_x = (int)(cub->cam.pos_x * MINIMAP_SCALE);
	player_y = (int)(cub->cam.pos_y * MINIMAP_SCALE);
	dir_len = 15.0;
	end_x = player_x + (int)(cub->cam.dir_x * dir_len);
	end_y = player_y + (int)(cub->cam.dir_y * dir_len);
	draw_minimap_pixel(&cub->gfx, end_x, end_y, 0xFF0000);
	draw_minimap_pixel(&cub->gfx, end_x + 1, end_y, 0xFF0000);
	draw_minimap_pixel(&cub->gfx, end_x, end_y + 1, 0xFF0000);
	draw_minimap_pixel(&cub->gfx, end_x - 1, end_y, 0xFF0000);
	draw_minimap_pixel(&cub->gfx, end_x, end_y - 1, 0xFF0000);
}