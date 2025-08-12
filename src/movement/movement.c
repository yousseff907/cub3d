/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:53:09 by odana             #+#    #+#             */
/*   Updated: 2025/08/12 16:53:27 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	move_forward(t_cub3d *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->cam.pos_x + cub->cam.dir_x * cub->cam.move_speed;
	new_y = cub->cam.pos_y + cub->cam.dir_y * cub->cam.move_speed;
	if (cub->map.grid[(int)new_y][(int)cub->cam.pos_x] != '1')
		cub->cam.pos_y = new_y;
	if (cub->map.grid[(int)cub->cam.pos_y][(int)new_x] != '1')
		cub->cam.pos_x = new_x;
}

void	move_backward(t_cub3d *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->cam.pos_x - cub->cam.dir_x * cub->cam.move_speed;
	new_y = cub->cam.pos_y - cub->cam.dir_y * cub->cam.move_speed;
	if (cub->map.grid[(int)new_y][(int)cub->cam.pos_x] != '1')
		cub->cam.pos_y = new_y;
	if (cub->map.grid[(int)cub->cam.pos_y][(int)new_x] != '1')
		cub->cam.pos_x = new_x;
}

void	move_left(t_cub3d *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->cam.pos_x - cub->cam.plane_x * cub->cam.move_speed;
	new_y = cub->cam.pos_y - cub->cam.plane_y * cub->cam.move_speed;
	if (cub->map.grid[(int)new_y][(int)cub->cam.pos_x] != '1')
		cub->cam.pos_y = new_y;
	if (cub->map.grid[(int)cub->cam.pos_y][(int)new_x] != '1')
		cub->cam.pos_x = new_x;
}

void	move_right(t_cub3d *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->cam.pos_x + cub->cam.plane_x * cub->cam.move_speed;
	new_y = cub->cam.pos_y + cub->cam.plane_y * cub->cam.move_speed;
	if (cub->map.grid[(int)new_y][(int)cub->cam.pos_x] != '1')
		cub->cam.pos_y = new_y;
	if (cub->map.grid[(int)cub->cam.pos_y][(int)new_x] != '1')
		cub->cam.pos_x = new_x;
}
