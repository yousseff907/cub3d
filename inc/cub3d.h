/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:04:55 by yitani            #+#    #+#             */
/*   Updated: 2025/08/12 17:31:27 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <errno.h>

# include "parsing.h"

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

# define ESC_KEY 65307
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define LEFT_KEY 65363
# define RIGHT_KEY 65361

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

double	dda(t_ray *ray, t_map *map);

void	draw_ceiling(t_graphics *gfx, int x, int end, int color);
void	draw_wall_segment(t_graphics *gfx, int x, int start, int end, int color);
void	draw_floor(t_graphics *gfx, int x, int start, int color);
void	put_pixel(t_graphics *gfx, int x, int y, int color);

int		key_hook(int keycode, t_cub3d *cub);
void	move_forward(t_cub3d *cub);
void	move_backward(t_cub3d *cub);
void	move_left(t_cub3d *cub);
void	move_right(t_cub3d *cub);
void	rotate_left(t_cub3d *cub);
void	rotate_right(t_cub3d *cub);
void	render_frame(t_cub3d *cub);
int		get_texture_pixel(char *tex_data, int tex_x, int tex_y);
int		calculate_texture_x(t_ray *ray);
void	draw_wall(t_graphics *gfx, int x, t_ray *ray, char *tex_data, int tex_x);
#endif