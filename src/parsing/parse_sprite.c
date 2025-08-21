/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 09:40:15 by odana             #+#    #+#             */
/*   Updated: 2025/08/21 20:47:40 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static char	*store_sprite_texture_path(char *path_str, t_cub3d *cub,
		t_sprite_cleanup *cleanup)
{
	char	*trimmed_path;

	trimmed_path = trim_whitespace(path_str);
	if (!trimmed_path)
	{
		free(cleanup->trimmed);
		free(cleanup->trimmed_sprite);
		free_split(cleanup->sprite_paths);
		free_split(cleanup->parsed_file);
		cleanup_exit(cub, "Error: Memory allocation failed", 1);
	}
	if (!validate_texture_file(trimmed_path))
	{
		free(cleanup->trimmed);
		ft_putstr_fd("Error: Invalid or missing texture file: ", 2);
		ft_putendl_fd(trimmed_path, 2);
		free(trimmed_path);
		free(cleanup->trimmed_sprite);
		free_split(cleanup->sprite_paths);
		free_split(cleanup->parsed_file);
		cleanup_exit(cub, "Error: Failed to load textures", 1);
	}
	return (trimmed_path);
}

static int	parse_sprite_paths(t_cub3d *cub, char **sprite_paths,
		t_sprite_cleanup *cleanup)
{
	int	i;

	i = 0;
	while (sprite_paths[i])
		i++;
	if (i != SPRITE_ANIMATION_FRAMES)
	{
		free_split(cleanup->sprite_paths);
		free(cleanup->trimmed_sprite);
		free(cleanup->trimmed);
		free_split(cleanup->parsed_file);
		cleanup_exit(cub, "Error: Sprite must have exactly 4 textures", 1);
	}
	i = 0;
	while (i < SPRITE_ANIMATION_FRAMES)
	{
		cub->txt.sprite_paths[i] = store_sprite_texture_path(sprite_paths[i],
				cub, cleanup);
		i++;
	}
	return (1);
}

void	store_sprite_textures(char *trimmed, char **parsed_file,
			t_cub3d *cub, char *sprite_str)
{
	t_sprite_cleanup	cleanup;

	cleanup.trimmed = trimmed;
	cleanup.parsed_file = parsed_file;
	cleanup.trimmed_sprite = trim_whitespace(sprite_str);
	if (!cleanup.trimmed_sprite)
	{
		free(trimmed);
		free_split(parsed_file);
		cleanup_exit(cub, "Error: Trimming failed", 1);
	}
	cleanup.sprite_paths = ft_split(cleanup.trimmed_sprite, ' ');
	if (!cleanup.sprite_paths)
	{
		free(trimmed);
		free_split(parsed_file);
		free(cleanup.trimmed_sprite);
		cleanup_exit(cub, "Error: Failed to parse sprite paths", 1);
	}
	parse_sprite_paths(cub, cleanup.sprite_paths, &cleanup);
	free(cleanup.trimmed_sprite);
	free_split(cleanup.sprite_paths);
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
