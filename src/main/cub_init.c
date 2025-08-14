/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:40:43 by yitani            #+#    #+#             */
/*   Updated: 2025/08/14 23:39:09 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	init_keys(t_cub3d *cub)
{
	cub->keys.w_pressed = 0;
	cub->keys.s_pressed = 0;
	cub->keys.a_pressed = 0;
	cub->keys.d_pressed = 0;
	cub->keys.left_pressed = 0;
	cub->keys.right_pressed = 0;
}

static void	init_graphics(t_cub3d *cub)
{
	cub->gfx.mlx_ptr = NULL;
	cub->gfx.win_ptr = NULL;
	cub->gfx.img_ptr = NULL;
	cub->gfx.img_data = NULL;
	cub->gfx.line_length = 0;
	cub->gfx.endian = 0;
}

static void	init_textures(t_cub3d *cub)
{
	cub->txt.north = NULL;
	cub->txt.south = NULL;
	cub->txt.east = NULL;
	cub->txt.west = NULL;
	cub->txt.north_data = NULL;
	cub->txt.south_data = NULL;
	cub->txt.east_data = NULL;
	cub->txt.west_data = NULL;
	cub->txt.north_path = NULL;
	cub->txt.south_path = NULL;
	cub->txt.east_path = NULL;
	cub->txt.west_path = NULL;
	cub->txt.north_length = 0;
	cub->txt.south_length = 0;
	cub->txt.east_length = 0;
	cub->txt.west_length = 0;
	cub->txt.floor_color = 0;
	cub->txt.ceiling_color = 0;
}

static void	init_map_camera(t_cub3d *cub)
{
	cub->map.grid = NULL;
	cub->map.width = 0;
	cub->map.height = 0;
	cub->map.player_spawn = '\0';
	cub->cam.pos_x = 0.0;
	cub->cam.pos_y = 0.0;
	cub->cam.dir_x = 0.0;
	cub->cam.dir_y = 0.0;
	cub->cam.plane_x = 0.0;
	cub->cam.plane_y = 0.0;
	cub->cam.move_speed = 0.05;
	cub->cam.rot_speed = 0.03;
}

void	init_cub3d(t_cub3d *cub)
{
	init_keys(cub);
	init_graphics(cub);
	init_textures(cub);
	init_map_camera(cub);
}
