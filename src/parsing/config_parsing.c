/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:59:17 by yitani            #+#    #+#             */
/*   Updated: 2025/08/14 20:11:25 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static char	*trim_whitespace(char *str)
{
	int		start;
	int		end;
	char	*result;
	int		len;
	
	start = 0;
	while (str[start] && is_space(str[start]))
		start++;
	
	end = ft_strlen(str) - 1;
	while (end >= start && is_space(str[end]))
		end--;
	
	len = end - start + 1;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	
	ft_strlcpy(result, str + start, len + 1);
	return (result);
}

static void	store_color(char *color_str, int *color)
{
	char	**rgb;
	int		r, g, b;
	char	*trimmed_color;
	
	trimmed_color = trim_whitespace(color_str);
	rgb = ft_split(trimmed_color, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
	{
		ft_putendl_fd("Error: Invalid color format", 2);
		exit(1);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		ft_putendl_fd("Error: RGB values must be 0-255", 2);
		exit(1);
	}
	*color = (r << 16) | (g << 8) | b;
	free(trimmed_color);
	free_split(rgb);
}

void	store_config_line(char *line, t_cub3d *cub)
{
	char	*trimmed;
	
	trimmed = trim_whitespace(line);
	
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
		cub->txt.north_path = ft_strdup(trim_whitespace(trimmed + 3));
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
		cub->txt.south_path = ft_strdup(trim_whitespace(trimmed + 3));
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
		cub->txt.west_path = ft_strdup(trim_whitespace(trimmed + 3));
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
		cub->txt.east_path = ft_strdup(trim_whitespace(trimmed + 3));
	else if (ft_strncmp(trimmed, "F ", 2) == 0)
		store_color(trimmed + 2, &cub->txt.floor_color);
	else if (ft_strncmp(trimmed, "C ", 2) == 0)
		store_color(trimmed + 2, &cub->txt.ceiling_color);
	else
	{
		ft_putendl_fd("Error: Invalid configuration line", 2);
		exit(1);
	}
	free(trimmed);
}
