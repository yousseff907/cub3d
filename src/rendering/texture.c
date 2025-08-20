/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:19:44 by odana             #+#    #+#             */
/*   Updated: 2025/08/20 09:48:40 by odana            ###   ########.fr       */
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

int	get_pixel_texture(char *tex_data, int tex_x, int tex_y, int line_length)
{
	int	color;

	if (tex_x < 0 || tex_x >= TEX_WIDTH || tex_y < 0 || tex_y >= TEX_HEIGHT)
		return (0x000000);
	color = *(int*)(tex_data + (tex_y * line_length + tex_x * 4));
	return (color);
}

void	load_wall_textures(t_cub3d *cub)
{
	int	bpp;
	int	endian;

	cub->txt.north = mlx_xpm_file_to_image(cub->gfx.mlx_ptr,
		cub->txt.north_path, &cub->txt.north_width, &cub->txt.north_height);
	if (!cub->txt.north)
		cleanup_exit(cub, "Error: Failed to load north texture", 1);
	cub->txt.north_data = mlx_get_data_addr(cub->txt.north, &bpp,
		&cub->txt.north_length, &endian);
	cub->txt.south = mlx_xpm_file_to_image(cub->gfx.mlx_ptr,
		cub->txt.south_path, &cub->txt.south_width, &cub->txt.south_height);
	if (!cub->txt.south)
		cleanup_exit(cub, "Error: Failed to load south texture", 1);
	cub->txt.south_data = mlx_get_data_addr(cub->txt.south, &bpp,
		&cub->txt.south_length, &endian);
}

void	load_wall_textures_2(t_cub3d *cub)
{
	int	bpp;
	int	endian;

	cub->txt.east = mlx_xpm_file_to_image(cub->gfx.mlx_ptr,
		cub->txt.east_path, &cub->txt.east_width, &cub->txt.east_height);
	if (!cub->txt.east)
		cleanup_exit(cub, "Error: Failed to load east texture", 1);
	cub->txt.east_data = mlx_get_data_addr(cub->txt.east, &bpp,
		&cub->txt.east_length, &endian);
	cub->txt.west = mlx_xpm_file_to_image(cub->gfx.mlx_ptr,
		cub->txt.west_path, &cub->txt.west_width, &cub->txt.west_height);
	if (!cub->txt.west)
		cleanup_exit(cub, "Error: Failed to load west texture", 1);
	cub->txt.west_data = mlx_get_data_addr(cub->txt.west, &bpp,
		&cub->txt.west_length, &endian);
}

char	*get_wall_data(t_ray *ray, t_textures *txt, int *line_length)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (*line_length = txt->east_length, txt->east_data);
		else
			return (*line_length = txt->west_length, txt->west_data);
	}
	else
	{
		if (ray->dir_y > 0)
			return (*line_length = txt->south_length, txt->south_data);
		else
			return (*line_length = txt->north_length, txt->north_data);
	}
}
