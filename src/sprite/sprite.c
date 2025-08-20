/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 09:28:08 by odana             #+#    #+#             */
/*   Updated: 2025/08/20 09:28:15 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	render_sprites(t_cub3d *cub)
{
	int	i;

	if (!cub->sprite_mgr.sprites || cub->sprite_mgr.sprite_count == 0)
		return ;
	i = 0;
	while (i < cub->sprite_mgr.sprite_count)
	{
		render_single_sprite(cub, &cub->sprite_mgr.sprites[i]);
		i++;
	}
}

void	cleanup_sprites(t_cub3d *cub)
{
	if (cub->sprite_mgr.sprites)
	{
		free(cub->sprite_mgr.sprites);
		cub->sprite_mgr.sprites = NULL;
	}
	cub->sprite_mgr.sprite_count = 0;
}