/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 23:41:49 by odana             #+#    #+#             */
/*   Updated: 2025/08/15 00:17:17 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	create_mlx(t_cub3d *cub)
{
	cub->gfx.mlx_ptr = mlx_init();
	if (!cub->gfx.mlx_ptr)
		cleanup_exit(cub, "Error: Failed to initialize MLX", 1);
	cub->gfx.win_ptr = mlx_new_window(cub->gfx.mlx_ptr, WIDTH, HEIGHT, "cub3D");
	if (!cub->gfx.win_ptr)
		cleanup_exit(cub, "Error: Failed to create window", 1);
}

void	create_image(t_cub3d *cub)
{
	int	bpp;

	cub->gfx.img_ptr = mlx_new_image(cub->gfx.mlx_ptr, WIDTH, HEIGHT);
	if (!cub->gfx.img_ptr)
		cleanup_exit(cub, "Error: Failed to create image", 1);
	cub->gfx.img_data = mlx_get_data_addr(cub->gfx.img_ptr, &bpp,
			&cub->gfx.line_length, &cub->gfx.endian);
	if (!cub->gfx.img_data)
		cleanup_exit(cub, "Error: Failed to get image data", 1);
}
void	cleanup_exit(t_cub3d *cub, char *msg, int exit_code)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	if (cub)
		cleanup_cub3d(cub);
	exit(exit_code);
}
