/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 09:40:15 by odana             #+#    #+#             */
/*   Updated: 2025/08/20 21:53:19 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	parse_sprite_paths(char *trimmed, char **parsed_file, t_cub3d *cub, char **sprite_paths)
{
	int	i;

	i = 0;
	while (sprite_paths[i])
		i++;
	if (i != SPRITE_ANIMATION_FRAMES)
	{
		free_split(sprite_paths);
		free(trimmed);
		free_split(parsed_file);
		return (0);
	}
	i = 0;
	while (i < SPRITE_ANIMATION_FRAMES)
	{
		cub->txt.sprite_paths[i] = store_texture_path(trimmed, parsed_file, sprite_paths[i], cub);
		i++;
	}
	return (1);
}

void	store_sprite_textures(char *trimmed, char **parsed_file, t_cub3d *cub, char *sprite_str)
{
	char	**sprite_paths;
	char	*trimmed_sprite;

	trimmed_sprite = trim_whitespace(sprite_str);
	if (!trimmed_sprite)
	{
		free(trimmed);
		free_split(parsed_file);
		cleanup_exit(cub, "Error: Trimming failed", 1);
	}
	sprite_paths = ft_split(trimmed_sprite, ' ');
	if (!sprite_paths)
	{
		free(trimmed);
		free_split(parsed_file);
		free(trimmed_sprite);
		cleanup_exit(cub, "Error: Failed to parse sprite paths", 1);
	}
	if (!parse_sprite_paths(trimmed, parsed_file, cub, sprite_paths))
	{
		free(trimmed_sprite);
		cleanup_exit(cub, "Error: Sprite must have exactly 4 textures", 1);
	}
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
			break ;
		i++;
	}
	if (i < SPRITE_ANIMATION_FRAMES)
	{
		i = 0;
		while (i < SPRITE_ANIMATION_FRAMES)
		{
			if (!cub->txt.sprite_paths[i])
			{
				ft_putendl_fd("Error: Incomplete sprite textures (SP)", 2);
				return (0);
			}
			i++;
		}
	}
	return (1);
}
