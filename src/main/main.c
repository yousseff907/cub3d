/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:20:04 by yitani            #+#    #+#             */
/*   Updated: 2025/08/14 23:57:46 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int main(int argc, char **argv)
{
	t_cub3d *cub;

	cub = malloc(sizeof(t_cub3d));
	if (!cub)
		cleanup_exit(cub, "Error: Memory allocation failed", 1);
	init_cub3d(cub);
	file_content_identification(argc, argv, cub);

	// program logic
	// initialize MLX
	// game loop

	cleanup_cub3d(cub);
	return (0);
}
