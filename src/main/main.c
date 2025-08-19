/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:20:04 by yitani            #+#    #+#             */
/*   Updated: 2025/08/20 02:20:34 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	nothing(void)
{
}

int main(int argc, char **argv)
{
	t_cub3d *cub;

	printf("DEBUG: Starting program\n");
	
	cub = malloc(sizeof(t_cub3d));
	if (!cub)
		cleanup_exit(cub, "Error: Memory allocation failed", 1);
	printf("DEBUG: Memory allocated\n");
	
	init_cub3d(cub);
	printf("DEBUG: cub3d initialized\n");
	
	// Parse the file and map FIRST
	file_content_identification(argc, argv, cub);
	printf("DEBUG: File parsing complete\n");
	
	// THEN initialize door system after map is loaded
	init_door_system(cub);
	printf("DEBUG: Door system initialized\n");
	
	setup_player_position(cub);
	printf("DEBUG: Player position set\n");
	
	init_player_direction(cub);
	printf("DEBUG: Player direction set\n");
	
	create_mlx(cub);
	printf("DEBUG: MLX created\n");
	
	create_image(cub);
	printf("DEBUG: Image created\n");
	
	load_textures(cub);
	printf("DEBUG: Textures loaded\n");
	
	render_frame(cub);
	printf("DEBUG: Initial frame rendered\n");
	
	mlx_mouse_hide(cub->gfx.mlx_ptr, cub->gfx.win_ptr);
	mlx_hook(cub->gfx.win_ptr, 2, 1L<<0, key_press, cub);
	mlx_hook(cub->gfx.win_ptr, 3, 1L<<1, key_release, cub);
	mlx_hook(cub->gfx.win_ptr, 17, 1L<<17, close_window, cub);
	mlx_hook(cub->gfx.win_ptr, 6, 1L<<6, mouse_move, cub);
	mlx_loop_hook(cub->gfx.mlx_ptr, game_loop, cub);
	printf("DEBUG: Hooks set up, starting main loop\n");
	
	mlx_loop(cub->gfx.mlx_ptr);
	cleanup_cub3d(cub);
	return (0);
}
