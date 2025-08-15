/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 11:04:02 by odana             #+#    #+#             */
/*   Updated: 2025/08/15 11:04:20 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	set_north_direction(t_cub3d *cub)
{
	cub->cam.dir_x = 0.0;
	cub->cam.dir_y = -1.0;
	cub->cam.plane_x = 0.66;
	cub->cam.plane_y = 0.0;
}

static void	set_south_direction(t_cub3d *cub)
{
	cub->cam.dir_x = 0.0;
	cub->cam.dir_y = 1.0;
	cub->cam.plane_x = -0.66;
	cub->cam.plane_y = 0.0;
}

static void	set_east_direction(t_cub3d *cub)
{
	cub->cam.dir_x = 1.0;
	cub->cam.dir_y = 0.0;
	cub->cam.plane_x = 0.0;
	cub->cam.plane_y = 0.66;
}

static void	set_west_direction(t_cub3d *cub)
{
	cub->cam.dir_x = -1.0;
	cub->cam.dir_y = 0.0;
	cub->cam.plane_x = 0.0;
	cub->cam.plane_y = -0.66;
}

void	init_player_direction(t_cub3d *cub)
{
	if (cub->map.player_spawn == 'N')
		set_north_direction(cub);
	else if (cub->map.player_spawn == 'S')
		set_south_direction(cub);
	else if (cub->map.player_spawn == 'E')
		set_east_direction(cub);
	else if (cub->map.player_spawn == 'W')
		set_west_direction(cub);
		cub->cam.dir_x, cub->cam.dir_y, cub->cam.plane_x, cub->cam.plane_y);
}
