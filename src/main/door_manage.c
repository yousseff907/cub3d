/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 00:33:30 by odana             #+#    #+#             */
/*   Updated: 2025/08/20 00:37:27 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	handle_door_trigger(t_door *door, double distance)
{
	if (distance < DOOR_TRIGGER_DISTANCE)
	{
		if (door->state == DOOR_CLOSED)
			door->state = DOOR_OPENING;
		door->frames_since_trigger = 0; 
	}
	else
	{
		door->frames_since_trigger++;
		if (door->frames_since_trigger > DOOR_AUTO_CLOSE_FRAMES 
			&& door->state == DOOR_OPEN)
			door->state = DOOR_CLOSING;
	}
}

static void	update_door_opening_animation(t_door *door)
{
	door->open_progress += DOOR_ANIMATION_SPEED;
	if (door->open_progress >= 1.0)
	{
		door->open_progress = 1.0;
		door->state = DOOR_OPEN;
	}
}

static void	update_door_closing_animation(t_door *door)
{
	door->open_progress -= DOOR_ANIMATION_SPEED;
	if (door->open_progress <= 0.0)
	{
		door->open_progress = 0.0;
		door->state = DOOR_CLOSED;
	}
}

static void	update_single_door(t_cub3d *cub, t_door *door)
{
	double	dx;
	double	dy;
    double  distance;
    
	dx = cub->cam.pos_x - (door->x + 0.5);
	dy = cub->cam.pos_y - (door->y + 0.5);
	distance = sqrt(dx * dx + dy * dy);
	handle_door_trigger(door, distance);
	if (door->state == DOOR_OPENING)
		update_door_opening_animation(door);
	else if (door->state == DOOR_CLOSING)
		update_door_closing_animation(door);
}

void	update_doors(t_cub3d *cub)
{
	int	i;

	if (!cub->door_mgr.doors || cub->door_mgr.door_count == 0)
		return ;
	i = 0;
	while (i < cub->door_mgr.door_count)
	{
		update_single_door(cub, &cub->door_mgr.doors[i]);
		i++;
	}
}