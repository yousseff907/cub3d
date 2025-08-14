/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parsing_validation.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:59:17 by yitani            #+#    #+#             */
/*   Updated: 2025/08/15 00:32:49 by yitani           ###   ########.fr       */
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

static char	*store_texture_path(char *path_str, t_cub3d *cub)
{
	char	*trimmed_path;
	
	trimmed_path = trim_whitespace(path_str);
	if (!trimmed_path)
		cleanup_exit(cub, "Error: Memory allocation failed", 1);
	if (!validate_texture_file(trimmed_path))
	{
		ft_putstr_fd("Error: Invalid or missing texture file: ", 2);
		ft_putendl_fd(trimmed_path, 2);
		free(trimmed_path);
		cleanup_exit(cub, "", 1);
	}
	
	return (trimmed_path);
}

static void	store_color(t_cub3d *cub, char *color_str, int *color)
{
	char	**rgb;
	int		r, g, b;
	char	*trimmed_color;
	
	trimmed_color = trim_whitespace(color_str);
	if (!trimmed_color)
		cleanup_exit(cub, "Error: Trimming failed", 1);
	rgb = ft_split(trimmed_color, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
	{
		free(trimmed_color);
		free_split(rgb);
		cleanup_exit(cub, "Error: Invalid color format", 1);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		free(trimmed_color);
		free_split(rgb);
		cleanup_exit(cub, "Error: RGB values must be 0-255", 1);
	}
	*color = (r << 16) | (g << 8) | b;
	return (free(trimmed_color), free_split(rgb));
}

void	store_config_line(char *line, t_cub3d *cub)
{
	char	*trimmed;
	
	trimmed = trim_whitespace(line);
	if (!trimmed)
		cleanup_exit(cub, "Error: Trimming failed", 1);
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
		cub->txt.north_path = store_texture_path(trimmed + 3, cub);
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
		cub->txt.south_path = store_texture_path(trimmed + 3, cub);
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
		cub->txt.west_path = store_texture_path(trimmed + 3, cub);
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
		cub->txt.east_path = store_texture_path(trimmed + 3, cub);
	else if (ft_strncmp(trimmed, "F ", 2) == 0)
		store_color(cub, trimmed + 2, &cub->txt.floor_color);
	else if (ft_strncmp(trimmed, "C ", 2) == 0)
		store_color(cub, trimmed + 2, &cub->txt.ceiling_color);
	else
	{
		free(trimmed);
		cleanup_exit(cub, "Error: Invalid configuration line", 1);
	}
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
	return (1);
}
