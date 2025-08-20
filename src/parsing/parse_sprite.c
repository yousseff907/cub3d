/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 09:40:15 by odana             #+#    #+#             */
/*   Updated: 2025/08/20 10:01:16 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	parse_sprite_paths(t_cub3d *cub, char **sprite_paths)
{
	int	i;

	i = 0;
	while (sprite_paths[i])
		i++;
	if (i != SPRITE_ANIMATION_FRAMES)
	{
		free_split(sprite_paths);
		cleanup_exit(cub, "Error: Sprite must have exactly 4 textures", 1);
	}
	i = 0;
	while (i < SPRITE_ANIMATION_FRAMES)
	{
		cub->txt.sprite_paths[i] = store_texture_path(sprite_paths[i], cub);
		i++;
	}
}

void	store_sprite_textures(t_cub3d *cub, char *sprite_str)
{
	char	**sprite_paths;
	char	*trimmed_sprite;

	trimmed_sprite = trim_whitespace(sprite_str);
	if (!trimmed_sprite)
		cleanup_exit(cub, "Error: Trimming failed", 1);
	sprite_paths = ft_split(trimmed_sprite, ' ');
	if (!sprite_paths)
	{
		free(trimmed_sprite);
		cleanup_exit(cub, "Error: Failed to parse sprite paths", 1);
	}
	parse_sprite_paths(cub, sprite_paths);
	free(trimmed_sprite);
	free_split(sprite_paths);
}

int	validate_sprites(t_cub3d *cub)
{
	int	i;

	i = 0;
	while (i < SPRITE_ANIMATION_FRAMES)
	{
		if (cub->txt.sprite_paths[i])
			break;
		i++;
	}
	if (i < SPRITE_ANIMATION_FRAMES)
	{
		i = 0;
		while (i < SPRITE_ANIMATION_FRAMES)
		{
			if (!cub->txt.sprite_paths[i])
				return (ft_putendl_fd("Error: Incomplete sprite textures (SP)", 2), 0);
			i++;
		}
	}
	return (1);
}