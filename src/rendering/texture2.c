/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 09:24:07 by odana             #+#    #+#             */
/*   Updated: 2025/08/20 16:26:15 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

char	*get_door_wall_texture(t_ray *ray, t_textures *txt, int *line_length)
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

static void	load_door_texture(t_cub3d *cub)
{
	int	bpp;
	int	endian;

	cub->txt.door = mlx_xpm_file_to_image(cub->gfx.mlx_ptr,
			"./textures/door.xpm", &cub->txt.door_width, &cub->txt.door_height);
	if (!cub->txt.door)
		cleanup_exit(cub, "Error: Failed to load door texture", 1);
	cub->txt.door_data = mlx_get_data_addr(cub->txt.door, &bpp,
			&cub->txt.door_length, &endian);
}

static void	load_single_sprite_texture(t_cub3d *cub, int i)
{
	int	bpp;
	int	endian;

	if (!cub->txt.sprite_paths[i])
		return ;
	cub->txt.sprite[i] = mlx_xpm_file_to_image(cub->gfx.mlx_ptr,
			cub->txt.sprite_paths[i], &cub->txt.sprite_width[i],
			&cub->txt.sprite_height[i]);
	if (!cub->txt.sprite[i])
		cleanup_exit(cub, "Error: Failed to load sprite texture", 1);
	cub->txt.sprite_data[i] = mlx_get_data_addr(cub->txt.sprite[i], &bpp,
			&cub->txt.sprite_length[i], &endian);
}

static void	load_sprite_textures(t_cub3d *cub)
{
	int	i;

	i = 0;
	while (i < SPRITE_ANIMATION_FRAMES)
	{
		load_single_sprite_texture(cub, i);
		i++;
	}
}

void	load_textures(t_cub3d *cub)
{
	load_wall_textures(cub);
	load_wall_textures_2(cub);
	load_door_texture(cub);
	load_sprite_textures(cub);
}
