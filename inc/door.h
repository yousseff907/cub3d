/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 00:03:53 by odana             #+#    #+#             */
/*   Updated: 2025/08/20 00:42:26 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOR_H
# define DOOR_H

# define HORIZONTAL 0
# define VERTICAL 1
# define DOOR_TRIGGER_DISTANCE 5
# define DOOR_AUTO_CLOSE_FRAMES 100
# define DOOR_ANIMATION_SPEED 0.05
# define DOOR_PASSABLE_THRESHOLD 0.75

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
void	update_doors(t_cub3d *cub);
int	    count_doors(t_cub3d *cub);
t_door	*find_door(t_cub3d *cub, int x, int y);
int	    can_pass(t_cub3d *cub, int x, int y);
int	    block_movement(t_cub3d *cub, int x, int y);
void	cleanup_doors(t_cub3d *cub);

#endif