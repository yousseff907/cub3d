/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 09:24:53 by odana             #+#    #+#             */
/*   Updated: 2025/08/20 10:11:43 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	count_sprites(t_cub3d *cub)
{
	int	i;
	int	j;
	int	sprite_count;

	sprite_count = 0;
	i = 0;
	while (i < cub->map.height)
	{
		j = 0;
		while (cub->map.grid[i] && cub->map.grid[i][j])
		{
			if (cub->map.grid[i][j] == 'X')
				sprite_count++;
			j++;
		}
		i++;
	}
	return (sprite_count);
}

static void	init_single_sprite(t_sprite *sprite, int x, int y)
{
	sprite->x = x + 0.5;
	sprite->y = y + 0.5;
	sprite->distance = 0.0;
	sprite->current_frame = 0;
	sprite->animation_counter = 0;
}

static void	find_and_init_sprites(t_cub3d *cub)
{
	int	i;
	int	j;
	int	sprite_index;

	sprite_index = 0;
	i = 0;
	while (i < cub->map.height)
	{
		j = 0;
		while (cub->map.grid[i] && cub->map.grid[i][j])
		{
			if (cub->map.grid[i][j] == 'X')
			{
				init_single_sprite(&cub->sprite_mgr.sprites[sprite_index], j, i);
				cub->map.grid[i][j] = '0';
				sprite_index++;
			}
			j++;
		}
		i++;
	}
}

static int	allocate_sprites(t_cub3d *cub)
{
	cub->sprite_mgr.sprite_count = count_sprites(cub);
	if (cub->sprite_mgr.sprite_count == 0)
	{
		cub->sprite_mgr.sprites = NULL;
		return (1);
	}
	cub->sprite_mgr.sprites = malloc(sizeof(t_sprite) * 
		cub->sprite_mgr.sprite_count);
	if (!cub->sprite_mgr.sprites)
		return (0);
	return (1);
}

void	init_sprite_system(t_cub3d *cub)
{
	if (!allocate_sprites(cub))
		cleanup_exit(cub, "Error: Failed to allocate memory for sprites", 1);
	if (cub->sprite_mgr.sprite_count > 0)
		find_and_init_sprites(cub);
}