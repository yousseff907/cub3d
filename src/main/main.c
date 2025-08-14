/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:20:04 by yitani            #+#    #+#             */
/*   Updated: 2025/08/15 01:36:18 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* Debug version of setup_player_position */

static void	setup_player_position(t_cub3d *cub)
{
	int	x;
	int	y;

	printf("DEBUG: Looking for player position...\n");
	printf("DEBUG: Map dimensions: %dx%d\n", cub->map.width, cub->map.height);
	
	if (!cub->map.grid)
	{
		printf("ERROR: Map grid is NULL!\n");
		return;
	}
	
	// First, let's print the entire map to see what we're working with
	printf("DEBUG: Complete map:\n");
	for (int i = 0; i < cub->map.height; i++)
	{
		if (cub->map.grid[i])
			printf("  Row %d: '%s' (len=%zu)\n", i, cub->map.grid[i], ft_strlen(cub->map.grid[i]));
		else
			printf("  Row %d: NULL\n", i);
	}
	
	y = 0;
	while (y < cub->map.height)
	{
		if (!cub->map.grid[y])
		{
			printf("DEBUG: Row %d is NULL, skipping\n", y);
			y++;
			continue;
		}
		
		x = 0;
		int row_len = ft_strlen(cub->map.grid[y]);
		printf("DEBUG: Checking row %d (length %d): '%s'\n", y, row_len, cub->map.grid[y]);
		
		while (x < row_len)
		{
			char c = cub->map.grid[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				printf("DEBUG: Found player '%c' at position (%d, %d)\n", c, x, y);
				cub->cam.pos_x = x + 0.5;
				cub->cam.pos_y = y + 0.5;
				cub->map.player_spawn = c;
				cub->map.grid[y][x] = '0';  // Replace player with empty space
				printf("DEBUG: Player position set to (%.1f, %.1f), spawn direction: %c\n", 
					cub->cam.pos_x, cub->cam.pos_y, cub->map.player_spawn);
				return ;
			}
			x++;
		}
		y++;
	}
	printf("DEBUG: No player spawn position found in any row!\n");
}


static void	init_player_direction(t_cub3d *cub)
{
	printf("DEBUG: Initializing player direction for spawn: %c\n", cub->map.player_spawn);
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
	printf("DEBUG: Direction set to (%.2f, %.2f), plane (%.2f, %.2f)\n", 
		cub->cam.dir_x, cub->cam.dir_y, cub->cam.plane_x, cub->cam.plane_y);
}

static void	validate_configuration(t_cub3d *cub)
{
	printf("DEBUG: Validating configuration...\n");
	
	printf("DEBUG: Checking texture paths:\n");
	printf("  North path: %s\n", cub->txt.north_path ? cub->txt.north_path : "NULL");
	printf("  South path: %s\n", cub->txt.south_path ? cub->txt.south_path : "NULL");
	printf("  East path: %s\n", cub->txt.east_path ? cub->txt.east_path : "NULL");
	printf("  West path: %s\n", cub->txt.west_path ? cub->txt.west_path : "NULL");
	
	printf("DEBUG: Checking colors:\n");
	printf("  Floor color: 0x%06X\n", cub->txt.floor_color);
	printf("  Ceiling color: 0x%06X\n", cub->txt.ceiling_color);
	
	if (!cub->txt.north_path || !cub->txt.south_path ||
		!cub->txt.east_path || !cub->txt.west_path)
	{
		printf("DEBUG: Missing texture paths!\n");
		cleanup_exit(cub, "Error: Missing texture paths", 1);
	}
	
	if (!cub->map.grid)
	{
		printf("DEBUG: No map found!\n");
		cleanup_exit(cub, "Error: No map found", 1);
	}
	
	printf("DEBUG: Map validation:\n");
	printf("  Map grid: %p\n", (void*)cub->map.grid);
	printf("  Map width: %d\n", cub->map.width);
	printf("  Map height: %d\n", cub->map.height);
	
	// Quick scan for player in map
	int player_found = 0;
	for (int y = 0; y < cub->map.height && cub->map.grid[y]; y++)
	{
		for (int x = 0; cub->map.grid[y][x]; x++)
		{
			char c = cub->map.grid[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				printf("  Found player '%c' at (%d, %d) during validation\n", c, x, y);
				player_found = 1;
			}
		}
	}
	
	if (!player_found)
	{
		printf("DEBUG: No player found during validation scan!\n");
	}
	
	printf("DEBUG: Configuration validation completed successfully!\n");
}



int main(int argc, char **argv)
{
	t_cub3d *cub;

	printf("DEBUG: Starting cub3D...\n");
	printf("DEBUG: Arguments: argc=%d\n", argc);
	if (argc > 1)
		printf("DEBUG: Map file: %s\n", argv[1]);

	cub = malloc(sizeof(t_cub3d));
	if (!cub)
		cleanup_exit(cub, "Error: Memory allocation failed", 1);
	
	printf("DEBUG: Memory allocated successfully\n");
	
	// Initialize all structures
	init_cub3d(cub);
	printf("DEBUG: Structures initialized\n");
	
	// Parse the .cub file and validate input
	file_content_identification(argc, argv, cub);
	printf("DEBUG: File parsed successfully\n");
	
	// Validate that we have all required configuration
	validate_configuration(cub);
	
	// Setup player position and direction from map
	setup_player_position(cub);
	init_player_direction(cub);
	
	// Initialize MLX and create window
	printf("DEBUG: Creating MLX...\n");
	create_mlx(cub);
	printf("DEBUG: MLX created, creating image...\n");
	create_image(cub);
	printf("DEBUG: Image created, loading textures...\n");
	
	// Load textures
	load_textures(cub);
	printf("DEBUG: Textures loaded, rendering first frame...\n");
	
	// Render initial frame
	render_frame(cub);
	printf("DEBUG: First frame rendered, setting up hooks...\n");
	
	// Set up event hooks
	mlx_mouse_hide(cub->gfx.mlx_ptr, cub->gfx.win_ptr);
	mlx_hook(cub->gfx.win_ptr, 2, 1L<<0, key_press, cub);         // KeyPress
	mlx_hook(cub->gfx.win_ptr, 3, 1L<<1, key_release, cub);       // KeyRelease
	mlx_hook(cub->gfx.win_ptr, 17, 1L<<17, close_window, cub);    // DestroyNotify (X button)
	mlx_hook(cub->gfx.win_ptr, 6, 1L<<6, mouse_move, cub);        // MotionNotify (mouse move)     // ButtonRelease (mouse release)
	mlx_loop_hook(cub->gfx.mlx_ptr, game_loop, cub);              // Main game loop
	
	printf("DEBUG: Hooks set up (including mouse), starting MLX loop...\n");
	
	// Start the MLX loop
	mlx_loop(cub->gfx.mlx_ptr);
	
	// Cleanup (this won't be reached unless mlx_loop exits)
	cleanup_cub3d(cub);
	return (0);
}

