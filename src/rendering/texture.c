/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:19:44 by odana             #+#    #+#             */
/*   Updated: 2025/08/12 20:58:42 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	calculate_texture(t_ray *ray)
{
	double	wall_hit;
	int		tex_x;

	if (ray->side == 0)
		wall_hit = ray->pos_y + ray->wall_dist * ray->dir_y;
	else
		wall_hit = ray->pos_x + ray->wall_dist * ray->dir_x;
	wall_hit -= floor(wall_hit);
	tex_x = (int)(wall_hit * TEX_WIDTH);
	if (ray->side == 0 && ray->dir_x > 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	return (tex_x);
}

int	get_pixel_texture(char *tex_data, int tex_x, int tex_y)
{
	int	color;

	if (tex_x < 0 || tex_x >= TEX_WIDTH || tex_y < 0 || tex_y >= TEX_HEIGHT)
		return (0x000000);
	color = *(int*)(tex_data + (tex_y * TEX_WIDTH + tex_x) * 4);
	return (color);
}

char	*get_wall_data(t_ray *ray, t_textures *txt)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (txt->east_data);
		else
			return (txt->west_data);
	}
	else
	{
		if (ray->dir_y > 0)
			return (txt->south_data);
		else
			return (txt->north_data);
	}
}