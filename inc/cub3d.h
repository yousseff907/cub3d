/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:04:55 by yitani            #+#    #+#             */
/*   Updated: 2025/08/11 23:42:59 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../src/minilibx-linux/mlx.h"
# include "../src/minilibx-linux/mlx_int.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../src/libft/libft.h"
# include "parsing.h"
# include <errno.h>

# define WIDTH 1920
# define HEIGHT 1080
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define BITS_PER_PIXEL 32

// Wall face constants

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

typedef struct s_ray
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;

	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;

	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	double	wall_dist;
}	t_ray;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	char	player_spawn;
}	t_map;

typedef struct s_camera
{
	double	pos_x;
	double	pos_y;

	double	dir_x;
	double	dir_y;

	double	plane_x;
	double	plane_y;

	double	move_speed;
	double	rot_speed;

	double	fov;
	int		render_distance;
}	t_camera;

typedef struct s_textures
{
	void	*north;
	char	*north_data;
	int		north_width;
	int		north_height;

	void	*south;
	char	*south_data;
	int		south_width;
	int		south_height;

	void	*east;
	char	*east_data;
	int		east_width;
	int		east_height;

	void	*west;
	char	*west_data;
	int		west_width;
	int		west_height;

	int		floor_color;
	int		ceiling_color;
}	t_textures;

typedef struct s_graphics
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		line_length;
	int		endian;
}	t_graphics;

typedef struct s_cub3d
{
	t_graphics	gfx;
	t_textures	txt;
	t_camera	cam;
	t_map		map;
}	t_cub3d;

#endif