/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parsing_validation.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:59:17 by yitani            #+#    #+#             */
/*   Updated: 2025/08/20 22:07:40 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	validate_texture_file(char *path)
{
	int		fd;
	char	*extension;

	if (!path || !*path)
		return (0);
	extension = ft_strrchr(path, '.');
	if (!extension || ft_strcmp(extension, ".xpm") != 0)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

char	*store_texture_path(char *trimmed, char **parsed_file,
			char *path_str, t_cub3d *cub)
{
	char	*trimmed_path;

	trimmed_path = trim_whitespace(path_str);
	if (!trimmed_path)
	{
		free(trimmed);
		free_split(parsed_file);
		cleanup_exit(cub, "Error: Memory allocation failed", 1);
	}
	if (!validate_texture_file(trimmed_path))
	{
		free(trimmed);
		ft_putstr_fd("Error: Invalid or missing texture file: ", 2);
		ft_putendl_fd(trimmed_path, 2);
		free(trimmed_path);
		free_split(parsed_file);
		cleanup_exit(cub, "", 1);
	}
	return (trimmed_path);
}

static void	store_color(char **file, char *trimmed, t_cub3d *cub, int *color)
{
	char		**rgb;
	long long	rgb_arr[4];
	char		*trimmed_color;
	char		*color_str;

	color_str = trimmed + 2;
	rgb_arr[3] = 0;
	trimmed_color = trim_whitespace(color_str);
	if (!trimmed_color)
		return (free_split(file), free(trimmed),
			cleanup_exit(cub, "Error: Trimming failed", 1));
	rgb = ft_split(trimmed_color, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		return (free(trimmed), free(trimmed_color), free_split(rgb),
			free_split(file),
			cleanup_exit(cub, "Error: Invalid color format", 1));
	rgb_arr[0] = custom_atoll(rgb[0], rgb_arr[3]);
	rgb_arr[1] = custom_atoll(rgb[1], rgb_arr[3]);
	rgb_arr[2] = custom_atoll(rgb[2], rgb_arr[3]);
	if (rgb_arr[0] < 0 || rgb_arr[0] > 255 || rgb_arr[1] < 0 || rgb_arr[1] > 255
		|| rgb_arr[2] < 0 || rgb_arr[2] > 255)
		return (free(trimmed_color), free_split(rgb), free(trimmed),
			free_split(file), cleanup_exit(cub, "Error: RGB values 0-255", 1));
	*color = (rgb_arr[0] << 16) | (rgb_arr[1] << 8) | rgb_arr[2];
	return (free(trimmed_color), free_split(rgb));
}

void	store_config_line(char **p, char *line, t_cub3d *cub)
{
	char	*trimmed;

	trimmed = trim_whitespace(line);
	if (!trimmed)
		return (free_split(p), cleanup_exit(cub, "Error: Trim", 1));
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
		cub->txt.north_path = store_texture_path(trimmed, p, trimmed + 3, cub);
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
		cub->txt.south_path = store_texture_path(trimmed, p, trimmed + 3, cub);
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
		cub->txt.west_path = store_texture_path(trimmed, p, trimmed + 3, cub);
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
		cub->txt.east_path = store_texture_path(trimmed, p, trimmed + 3, cub);
	else if (ft_strncmp(trimmed, "F ", 2) == 0)
		store_color(p, trimmed, cub, &cub->txt.floor_color);
	else if (ft_strncmp(trimmed, "C ", 2) == 0)
		store_color(p, trimmed, cub, &cub->txt.ceiling_color);
	else if (ft_strncmp(trimmed, "SP ", 3) == 0)
		store_sprite_textures(trimmed, p, cub, trimmed + 3);
	else
		return (free(trimmed), cleanup_exit(cub, "Error: Invalid line", 1));
	free(trimmed);
}

int	validate_complete_config(t_cub3d *cub)
{
	if (!cub->txt.north_path)
		return (ft_putendl_fd("Error: Missing north texture (NO)", 2), 0);
	if (!cub->txt.south_path)
		return (ft_putendl_fd("Error: Missing south texture (SO)", 2), 0);
	if (!cub->txt.west_path)
		return (ft_putendl_fd("Error: Missing west texture (WE)", 2), 0);
	if (!cub->txt.east_path)
		return (ft_putendl_fd("Error: Missing east texture (EA)", 2), 0);
	if (cub->txt.floor_color == -1)
		return (ft_putendl_fd("Error: Missing floor color (F)", 2), 0);
	if (cub->txt.ceiling_color == -1)
		return (ft_putendl_fd("Error: Missing ceiling color (C)", 2), 0);
	if (!validate_sprites(cub))
		return (0);
	return (1);
}
