/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:53:59 by odana             #+#    #+#             */
/*   Updated: 2025/08/15 01:42:20 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	rotate_camera(t_cub3d *cub, double angle)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	
	old_dir_x = cub->cam.dir_x;
	old_plane_x = cub->cam.plane_x;
	
	cub->cam.dir_x = cub->cam.dir_x * cos_angle - cub->cam.dir_y * sin_angle;
	cub->cam.dir_y = old_dir_x * sin_angle + cub->cam.dir_y * cos_angle;
	cub->cam.plane_x = cub->cam.plane_x * cos_angle - cub->cam.plane_y * sin_angle;
	cub->cam.plane_y = old_plane_x * sin_angle + cub->cam.plane_y * cos_angle;
}

int	mouse_move(int x, int y, t_cub3d *cub)
{
	int		delta_x;
	double	rotation_angle;
	
	delta_x = x - (WIDTH / 2);
	if (abs(delta_x) < 3)
		return (0);
	rotation_angle = (double)delta_x * 0.001;
	rotate_camera(cub, rotation_angle);
	mlx_mouse_move(cub->gfx.mlx_ptr, cub->gfx.win_ptr, WIDTH / 2, HEIGHT / 2);
	(void)y;
	return (0);
}

