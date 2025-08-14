/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:20:04 by yitani            #+#    #+#             */
/*   Updated: 2025/08/15 00:22:04 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	setup_player_position(t_cub3d *cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < cub->map.height)
	{
		x = 0;
		while (x < (int)ft_strlen(cub->map.grid[y]))
		{
			if (cub->map.grid[y][x] == 'N' || cub->map.grid[y][x] == 'S' ||
				cub->map.grid[y][x] == 'E' || cub->map.grid[y][x] == 'W')
			{
				cub->cam.pos_x = x + 0.5;
				cub->cam.pos_y = y + 0.5;
				cub->map.player_spawn = cub->map.grid[y][x];
				cub->map.grid[y][x] = '0';  // Replace player with empty space
				return ;
			}
			x++;
		}
		y++;
	}
}

static void	init_player_direction(t_cub3d *cub)
{
	if (cub->map.player_spawn == 'N')
	{
		cub->cam.dir_x = 0.0;
		cub->cam.dir_y = -1.0;
		cub->cam.plane_x = 0.66;
		cub->cam.plane_y = 0.0;
	}
	else if (cub->map.player_spawn == 'S')
	{
		cub->cam.dir_x = 0.0;
		cub->cam.dir_y = 1.0;
		cub->cam.plane_x = -0.66;
		cub->cam.plane_y = 0.0;
	}
	else if (cub->map.player_spawn == 'E')
	{
		cub->cam.dir_x = 1.0;
		cub->cam.dir_y = 0.0;
		cub->cam.plane_x = 0.0;
		cub->cam.plane_y = 0.66;
	}
	else if (cub->map.player_spawn == 'W')
	{
		cub->cam.dir_x = -1.0;
		cub->cam.dir_y = 0.0;
		cub->cam.plane_x = 0.0;
		cub->cam.plane_y = -0.66;
	}
}

static void	validate_configuration(t_cub3d *cub)
{
	if (!cub->txt.north_path || !cub->txt.south_path ||
		!cub->txt.east_path || !cub->txt.west_path)
		cleanup_exit(cub, "Error: Missing texture paths", 1);
	
	if (!cub->map.grid)
		cleanup_exit(cub, "Error: No map found", 1);
	
	// Validate that player spawn position was found and set
	if (cub->map.player_spawn == '\0')
		cleanup_exit(cub, "Error: No player spawn position found", 1);
}

int main(int argc, char **argv)
{
	t_cub3d *cub;

	cub = malloc(sizeof(t_cub3d));
	if (!cub)
		cleanup_exit(cub, "Error: Memory allocation failed", 1);
	
	// Initialize all structures
	init_cub3d(cub);
	
	// Parse the .cub file and validate input
	file_content_identification(argc, argv, cub);
	
	// Validate that we have all required configuration
	validate_configuration(cub);
	
	// Setup player position and direction from map
	setup_player_position(cub);
	init_player_direction(cub);
	
	// Initialize MLX and create window
	create_mlx(cub);
	create_image(cub);
	
	// Load textures
	load_textures(cub);
	
	// Render initial frame
	render_frame(cub);
	
	// Set up event hooks
	mlx_hook(cub->gfx.win_ptr, 2, 1L<<0, key_press, cub);      // KeyPress
	mlx_hook(cub->gfx.win_ptr, 3, 1L<<1, key_release, cub);    // KeyRelease
	mlx_hook(cub->gfx.win_ptr, 17, 1L<<17, close_window, cub); // DestroyNotify (X button)
	mlx_loop_hook(cub->gfx.mlx_ptr, game_loop, cub);           // Main game loop
	
	// Start the MLX loop
	mlx_loop(cub->gfx.mlx_ptr);
	
	// Cleanup (this won't be reached unless mlx_loop exits)
	cleanup_cub3d(cub);
	return (0);
}
