/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 00:03:53 by odana             #+#    #+#             */
/*   Updated: 2025/08/20 00:19:09 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOR_H
# define DOOR_H

# define HORIZONTAL 0
# define VERTICAL 1

typedef enum e_door_state
{
    DOOR_CLOSED,
    DOOR_OPENING,
    DOOR_OPEN,
    DOOR_CLOSING
} t_door_state;

typedef struct s_door
{
    int         x;
    int         y;
    t_door_state state;
    double      open_progress;
    int         orientation;
    int         frames_since_trigger;
} t_door;

typedef struct s_door_manager
{
    t_door  *doors;
    int     door_count;
} t_door_manager;

void	init_door_system(t_cub3d *cub);
int	    count_doors(t_cub3d *cub);

#endif