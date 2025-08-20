/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 09:25:11 by odana             #+#    #+#             */
/*   Updated: 2025/08/20 14:53:24 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	update_sprite_animation(t_sprite *sprite)
{
	sprite->animation_counter++;
	if (sprite->animation_counter >= SPRITE_ANIMATION_SPEED)
	{
		sprite->animation_counter = 0;
		sprite->current_frame++;
		if (sprite->current_frame >= SPRITE_ANIMATION_FRAMES)
			sprite->current_frame = 0;
	}
}

static void	calculate_single_sprite_distance(t_sprite *sprite, t_camera *cam)
{
	double	dx;
	double	dy;

	dx = cam->pos_x - sprite->x;
	dy = cam->pos_y - sprite->y;
	sprite->distance = (dx * dx) + (dy * dy);
}

void	calculate_sprite_distances(t_cub3d *cub)
{
	int	i;

	if (!cub->sprite_mgr.sprites || cub->sprite_mgr.sprite_count == 0)
		return ;
	i = 0;
	while (i < cub->sprite_mgr.sprite_count)
	{
		calculate_single_sprite_distance(&cub->sprite_mgr.sprites[i],
			&cub->cam);
		i++;
	}
}

static void	swap_sprites(t_sprite *a, t_sprite *b)
{
	t_sprite	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	sort_sprites_by_distance(t_cub3d *cub)
{
	int	i;
	int	j;

	if (!cub->sprite_mgr.sprites || cub->sprite_mgr.sprite_count <= 1)
		return ;
	i = 0;
	while (i < cub->sprite_mgr.sprite_count - 1)
	{
		j = 0;
		while (j < cub->sprite_mgr.sprite_count - i - 1)
		{
			if (cub->sprite_mgr.sprites[j].distance
				< cub->sprite_mgr.sprites[j + 1].distance)
				swap_sprites(&cub->sprite_mgr.sprites[j],
					&cub->sprite_mgr.sprites[j + 1]);
			j++;
		}
		i++;
	}
}

void	update_sprites(t_cub3d *cub)
{
	int	i;

	if (!cub->sprite_mgr.sprites || cub->sprite_mgr.sprite_count == 0)
		return ;
	i = 0;
	while (i < cub->sprite_mgr.sprite_count)
	{
		update_sprite_animation(&cub->sprite_mgr.sprites[i]);
		i++;
	}
	calculate_sprite_distances(cub);
	sort_sprites_by_distance(cub);
}
