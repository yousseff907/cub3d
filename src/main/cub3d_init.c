/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:40:43 by yitani            #+#    #+#             */
/*   Updated: 2025/08/14 19:41:25 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_cub3d(t_cub3d *cub)
{
	cub->gfx.mlx_ptr = NULL;
	cub->gfx.win_ptr = NULL;
	cub->gfx.img_ptr = NULL;
	cub->gfx.img_data = NULL;
	cub->txt.north = NULL;
	cub->txt.south = NULL;
	cub->txt.east = NULL;
	cub->txt.west = NULL;
	cub->txt.north_data = NULL;
	cub->txt.south_data = NULL;
	cub->txt.east_data = NULL;
	cub->txt.west_data = NULL;
	cub->txt.floor_color = 0;
	cub->txt.ceiling_color = 0;
	cub->map.grid = NULL;
	cub->map.width = 0;
	cub->map.height = 0;
	cub->map.player_spawn = '\0';
	cub->cam.pos_x = 0.0;
	cub->cam.pos_y = 0.0;
}
