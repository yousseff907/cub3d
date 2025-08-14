/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 22:57:12 by odana             #+#    #+#             */
/*   Updated: 2025/08/15 00:17:52 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	destroy_images(t_cub3d *cub)
{
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
    }
}

static void cleanup_textures(t_cub3d *cub)
{
    if (!cub)
        return;
    if (cub->txt.north_path)
    {
        free(cub->txt.north_path);
        cub->txt.north_path = NULL;
    }
    if (cub->txt.south_path)
    {
        free(cub->txt.south_path);
        cub->txt.south_path = NULL;
    }
    if (cub->txt.east_path)
    {
        free(cub->txt.east_path);
        cub->txt.east_path = NULL;
    }
    if (cub->txt.west_path)
    {
        free(cub->txt.west_path);
        cub->txt.west_path = NULL;
    }
    destroy_images(cub);
    cub->txt.north = NULL;
    cub->txt.south = NULL;
    cub->txt.east = NULL;
    cub->txt.west = NULL;
}

static void cleanup_map(t_cub3d *cub)
{
    int i;
    
    if (!cub || !cub->map.grid)
        return;
    
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

static void cleanup_graphics(t_cub3d *cub)
{
    if (!cub)
        return;
    if (cub->gfx.img_ptr && cub->gfx.mlx_ptr)
    {
        mlx_destroy_image(cub->gfx.mlx_ptr, cub->gfx.img_ptr);
        cub->gfx.img_ptr = NULL;
        cub->gfx.img_data = NULL;
    }
    if (cub->gfx.win_ptr && cub->gfx.mlx_ptr)
    {
        mlx_destroy_window(cub->gfx.mlx_ptr, cub->gfx.win_ptr);
        cub->gfx.win_ptr = NULL;
    }
    if (cub->gfx.mlx_ptr)
    {
        mlx_destroy_display(cub->gfx.mlx_ptr);
        free(cub->gfx.mlx_ptr);
        cub->gfx.mlx_ptr = NULL;
    }
}

void cleanup_cub3d(t_cub3d *cub)
{
    if (!cub)
        return;
    cleanup_textures(cub);
    cleanup_map(cub);
    cleanup_graphics(cub);
    free(cub);
}

