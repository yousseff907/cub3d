/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:20:04 by yitani            #+#    #+#             */
/*   Updated: 2025/08/20 09:31:07 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	nothing(void)
{
}

int main(int argc, char **argv)
{
	t_cub3d *cub;
	
	cub = malloc(sizeof(t_cub3d));
	if (!cub)
		cleanup_exit(cub, "Error: Memory allocation failed", 1);
	init_cub3d(cub);
	file_content_identification(argc, argv, cub);
	init_door_system(cub);
	init_sprite_system(cub);
	setup_player_position(cub);
	init_player_direction(cub);
	create_mlx(cub);
	create_image(cub);
	load_textures(cub);
	render_frame(cub);
	mlx_mouse_hide(cub->gfx.mlx_ptr, cub->gfx.win_ptr);
	mlx_hook(cub->gfx.win_ptr, 2, 1L<<0, key_press, cub);
	mlx_hook(cub->gfx.win_ptr, 3, 1L<<1, key_release, cub);
	mlx_hook(cub->gfx.win_ptr, 17, 1L<<17, close_window, cub);
	mlx_hook(cub->gfx.win_ptr, 6, 1L<<6, mouse_move, cub);
	mlx_loop_hook(cub->gfx.mlx_ptr, game_loop, cub);	
	mlx_loop(cub->gfx.mlx_ptr);
	cleanup_cub3d(cub);
	return (0);
}
