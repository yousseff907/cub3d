/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:04:55 by yitani            #+#    #+#             */
/*   Updated: 2025/08/20 10:22:16 by odana            ###   ########.fr       */
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
# include <stdio.h>
# include <string.h>
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

# define HORIZONTAL 0
# define VERTICAL 1
# define DOOR_TRIGGER_DISTANCE 2
# define DOOR_AUTO_CLOSE_FRAMES 100
# define DOOR_ANIMATION_SPEED 0.02
# define DOOR_PASSABLE_THRESHOLD 0.9

# define SPRITE_ANIMATION_FRAMES 4
# define SPRITE_ANIMATION_SPEED 100

typedef struct s_minimap
{
	int	scale;
	int	margin;
	int	width;
	int	height;
	int	max_size;
	int	color;
	int	map_x;
	int	map_y;
	int	pixel_x;
	int	pixel_y;
	int	center_x;
	int	center_y;
	int	dot_size;
	int	offset_x;
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
	int	steps;
}	t_minimap;

typedef enum e_door_state
{
	DOOR_CLOSED,
	DOOR_OPENING,
	DOOR_OPEN,
	DOOR_CLOSING
}	t_door_state;

typedef struct s_door
{
	int			x;
	int			y;
	t_door_state	state;
	double		open_progress;
	int			orientation;
	int			frames_since_trigger;
}	t_door;

typedef struct s_door_manager
{
	t_door	*doors;
	int		door_count;
}	t_door_manager;

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

	void	*door;
	char	*door_data;
	int		door_width;
	int		door_height;
	int		door_length;

	void	*sprite[SPRITE_ANIMATION_FRAMES];
	char	*sprite_data[SPRITE_ANIMATION_FRAMES];
	char	*sprite_paths[SPRITE_ANIMATION_FRAMES];
	int		sprite_width[SPRITE_ANIMATION_FRAMES];
	int		sprite_height[SPRITE_ANIMATION_FRAMES];
	int		sprite_length[SPRITE_ANIMATION_FRAMES];

	int		floor_color;
	int		ceiling_color;
}	t_textures;

typedef struct s_sprite
{
	double	x;
	double	y;
	double	distance;
	int		current_frame;
	int		animation_counter;
}	t_sprite;

typedef struct s_sprite_manager
{
	t_sprite	*sprites;
	int			sprite_count;
}	t_sprite_manager;

typedef struct s_sprite_draw
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		sprite_screen_x;
	int		sprite_height;
	int		sprite_width;
	int		draw_start_y;
	int		draw_end_y;
	int		draw_start_x;
	int		draw_end_x;
}	t_sprite_draw;

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
	int	w_pressed;
	int	s_pressed;
	int	a_pressed;
	int	d_pressed;
}	t_keys;

typedef struct s_cub3d
{
	t_door_manager	door_mgr;
	t_sprite_manager	sprite_mgr;
	t_graphics		gfx;
	t_textures		txt;
	t_camera		cam;
	t_map			map;
	t_keys			keys;
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


void	init_cub3d(t_cub3d *cub);

// MLX setup functions
void	create_mlx(t_cub3d *cub);
void	create_image(t_cub3d *cub);
void	load_wall_textures(t_cub3d *cub);
void	load_wall_textures_2(t_cub3d *cub);
void	load_textures(t_cub3d *cub);

// Player setup functions

void	setup_player_position(t_cub3d *cub);
void	init_player_direction(t_cub3d *cub);

// Cleanup functions
void	cleanup_cub3d(t_cub3d *cub);
int		close_window(t_cub3d *cub);
void	cleanup_exit(t_cub3d *cub, char *msg, int exit_code);

// Raycasting
double	dda(t_ray *ray, t_cub3d *cub);

// Drawing functions
void	draw_ceiling(t_graphics *gfx, int x, int end, int color);
void	draw_floor(t_graphics *gfx, int x, int start, int color);
void	put_pixel(t_graphics *gfx, int x, int y, int color);
void	draw_wall_column(t_graphics *gfx, int screen_x,
			t_ray *ray, t_textures *txt);

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

// Texture functions

int		get_pixel_texture(char *tex_data, int tex_x, int tex_y,
			int line_length);
int		calculate_texture(t_ray *ray);
char	*get_wall_data(t_ray *ray, t_textures *txt, int *line_length);
void	nothing(void);

// Door system

void	init_door_system(t_cub3d *cub);
void	update_doors(t_cub3d *cub);
void	cleanup_doors(t_cub3d *cub);

int		count_doors(t_cub3d *cub);
t_door	*find_door(t_cub3d *cub, int x, int y);
int		can_pass(t_cub3d *cub, int x, int y);
int		block_movement(t_cub3d *cub, int x, int y);

int		calculate_door_tex_x(t_door *door, t_ray *ray);
char	*get_door_wall_texture(t_ray *ray, t_textures *txt, int *line_length);
void	draw_door_column(t_cub3d *cub, int screen_x, t_ray *ray, t_door *door);

// Sprite system

void	init_sprite_system(t_cub3d *cub);
void	update_sprites(t_cub3d *cub);
void	render_sprites(t_cub3d *cub);
void	cleanup_sprites(t_cub3d *cub);
int		validate_sprites(t_cub3d *cub);
int		count_sprites(t_cub3d *cub);
void	calculate_sprite_distances(t_cub3d *cub);
void	sort_sprites_by_distance(t_cub3d *cub);
void	store_sprite_textures(t_cub3d *cub, char *sprite_str);
void	render_single_sprite(t_cub3d *cub, t_sprite *sprite);
int		has_line_of_sight(t_cub3d *cub, double sprite_x, double sprite_y);

// Minimap system

t_minimap	init_minimap(t_cub3d *cub);

int			get_cell_color(char cell, t_cub3d *cub, int x, int y);
int			get_player_dot_size(int scale);
int			get_direction_length(int scale);
int			is_player_in_bounds(t_cub3d *cub);

void		draw_minimap_pixel(t_graphics *gfx, int x, int y, t_minimap *minimap);
void		draw_minimap_square(t_graphics *gfx, t_minimap *minimap);
void		draw_minimap(t_cub3d *cub);

void		draw_minimap_border(t_graphics *gfx, t_minimap *minimap);

void		draw_player_on_minimap(t_cub3d *cub);
void		draw_player_direction(t_cub3d *cub);

#endif