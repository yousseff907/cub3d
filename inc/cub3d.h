/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:04:55 by yitani            #+#    #+#             */
/*   Updated: 2025/08/15 11:10:00 by odana            ###   ########.fr       */
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
	char	*north_path;
	int		north_width;
	int		north_height;
	int		north_length;
	
	void	*south;
	char	*south_data;
	char	*south_path;
	int		south_width;
	int		south_height;
	int		south_length;
	
	void	*east;
	char	*east_data;
	char	*east_path;
	int		east_width;
	int		east_height;
	int		east_length;
	
	void	*west;
	char	*west_data;
	char	*west_path;
	int		west_width;
	int		west_height;
	int		west_length;

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

typedef struct s_keys
{
	int w_pressed;
	int s_pressed;
	int a_pressed;
	int d_pressed;
} t_keys;

typedef struct s_cub3d
{
	t_graphics	gfx;
	t_textures	txt;
	t_camera	cam;
	t_map		map;
	t_keys		keys;
}	t_cub3d;

typedef struct s_wall_draw
{
	int		line_height;
	int		line_length;
	int		draw_start;
	int		draw_end;
	int		screen_x;
	double	step;
}	t_wall_draw;


// Structure initialization functions
void	init_cub3d(t_cub3d *cub);

// MLX setup functions
void	create_mlx(t_cub3d *cub);
void	create_image(t_cub3d *cub);
void	load_textures(t_cub3d *cub);

// Player setup functions

void	setup_player_position(t_cub3d *cub);
void	init_player_direction(t_cub3d *cub);

// Cleanup functions
void	cleanup_cub3d(t_cub3d *cub);
int		close_window(t_cub3d *cub);
void	cleanup_exit(t_cub3d *cub, char *msg, int exit_code);

// Raycasting
double	dda(t_ray *ray, t_map *map);

// Drawing functions
void	draw_ceiling(t_graphics *gfx, int x, int end, int color);
void	draw_floor(t_graphics *gfx, int x, int start, int color);
void	put_pixel(t_graphics *gfx, int x, int y, int color);
void	draw_wall_column(t_graphics *gfx, int screen_x, t_ray *ray, t_textures *txt);

// Movement
int		key_release(int keycode, t_cub3d *cub);
int		key_press(int keycode, t_cub3d *cub);
int		game_loop(t_cub3d *cub);
void	move_forward(t_cub3d *cub);
void	move_backward(t_cub3d *cub);
void	move_left(t_cub3d *cub);
void	move_right(t_cub3d *cub);
int		mouse_move(int x, int y, t_cub3d *cub);

// Rendering
void	render_frame(t_cub3d *cub);

// Texture functions (UPDATED SIGNATURES)
int		get_pixel_texture(char *tex_data, int tex_x, int tex_y, int line_length);
int		calculate_texture(t_ray *ray);
char	*get_wall_data(t_ray *ray, t_textures *txt, int *line_length);

#endif