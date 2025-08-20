/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 22:57:12 by odana             #+#    #+#             */
/*   Updated: 2025/08/20 16:20:32 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	destroy_images(t_cub3d *cub)
{
	int	i;

	if (cub->gfx.mlx_ptr)
	{
		if (cub->txt.north)
			mlx_destroy_image(cub->gfx.mlx_ptr, cub->txt.north);
		if (cub->txt.south)
			mlx_destroy_image(cub->gfx.mlx_ptr, cub->txt.south);
		if (cub->txt.east)
			mlx_destroy_image(cub->gfx.mlx_ptr, cub->txt.east);
		if (cub->txt.west)
			mlx_destroy_image(cub->gfx.mlx_ptr, cub->txt.west);
		if (cub->txt.door)
			mlx_destroy_image(cub->gfx.mlx_ptr, cub->txt.door);
		i = 0;
		while (i < SPRITE_ANIMATION_FRAMES)
		{
			if (cub->txt.sprite[i])
				mlx_destroy_image(cub->gfx.mlx_ptr, cub->txt.sprite[i]);
			i++;
		}
	}
}

static void	cleanup_texture_paths(t_cub3d *cub)
{
	int	i;

	if (cub->txt.north_path)
		free(cub->txt.north_path);
	if (cub->txt.south_path)
		free(cub->txt.south_path);
	if (cub->txt.east_path)
		free(cub->txt.east_path);
	if (cub->txt.west_path)
		free(cub->txt.west_path);
	i = 0;
	while (i < SPRITE_ANIMATION_FRAMES)
	{
		if (cub->txt.sprite_paths[i])
			free(cub->txt.sprite_paths[i]);
		i++;
	}
}

static void	cleanup_textures(t_cub3d *cub)
{
	if (!cub)
		return ;
	cleanup_texture_paths(cub);
	destroy_images(cub);
	cub->txt.north_path = NULL;
	cub->txt.south_path = NULL;
	cub->txt.east_path = NULL;
	cub->txt.west_path = NULL;
	cub->txt.north = NULL;
	cub->txt.south = NULL;
	cub->txt.east = NULL;
	cub->txt.west = NULL;
	cub->txt.door = NULL;
}

static void	cleanup_map(t_cub3d *cub)
{
	int	i;

	if (!cub || !cub->map.grid)
		return ;
	i = 0;
	while (cub->map.grid[i])
	{
		free(cub->map.grid[i]);
		cub->map.grid[i] = NULL;
		i++;
	}
	free(cub->map.grid);
	cub->map.grid = NULL;
	cub->map.width = 0;
	cub->map.height = 0;
}

void	cleanup_cub3d(t_cub3d *cub)
{
	if (!cub)
		return ;
	cleanup_textures(cub);
	cleanup_map(cub);
	cleanup_doors(cub);
	cleanup_sprites(cub);
	if (cub->gfx.img_ptr && cub->gfx.mlx_ptr)
		mlx_destroy_image(cub->gfx.mlx_ptr, cub->gfx.img_ptr);
	if (cub->gfx.win_ptr && cub->gfx.mlx_ptr)
		mlx_destroy_window(cub->gfx.mlx_ptr, cub->gfx.win_ptr);
	if (cub->gfx.mlx_ptr)
	{
		mlx_destroy_display(cub->gfx.mlx_ptr);
		free(cub->gfx.mlx_ptr);
	}
	free(cub);
}
