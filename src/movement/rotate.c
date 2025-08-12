/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:53:59 by odana             #+#    #+#             */
/*   Updated: 2025/08/12 16:54:10 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	rotate_left(t_cub3d *cub)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->cam.dir_x;
	old_plane_x = cub->cam.plane_x;
	cub->cam.dir_x = cub->cam.dir_x * cos(cub->cam.rot_speed) - cub->cam.dir_y * sin(cub->cam.rot_speed);
	cub->cam.dir_y = old_dir_x * sin(cub->cam.rot_speed) + cub->cam.dir_y * cos(cub->cam.rot_speed);
	cub->cam.plane_x = cub->cam.plane_x * cos(cub->cam.rot_speed) - cub->cam.plane_y * sin(cub->cam.rot_speed);
	cub->cam.plane_y = old_plane_x * sin(cub->cam.rot_speed) + cub->cam.plane_y * cos(cub->cam.rot_speed);
}

void	rotate_right(t_cub3d *cub)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->cam.dir_x;
	old_plane_x = cub->cam.plane_x;
	cub->cam.dir_x = cub->cam.dir_x * cos(-cub->cam.rot_speed) - cub->cam.dir_y * sin(-cub->cam.rot_speed);
	cub->cam.dir_y = old_dir_x * sin(-cub->cam.rot_speed) + cub->cam.dir_y * cos(-cub->cam.rot_speed);
	cub->cam.plane_x = cub->cam.plane_x * cos(-cub->cam.rot_speed) - cub->cam.plane_y * sin(-cub->cam.rot_speed);
	cub->cam.plane_y = old_plane_x * sin(-cub->cam.rot_speed) + cub->cam.plane_y * cos(-cub->cam.rot_speed);
}