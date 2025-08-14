/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:21:16 by yitani            #+#    #+#             */
/*   Updated: 2025/08/14 19:39:26 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	is_empty_line(char	*line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n'
			&& line[i] != '\r' && line[i] != '\v' && line[i] != '\f')
			return (0);
		i++;
	}
	return (1);
}

int	is_config_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (is_space(line[i]))
		{
			i++;
			continue ;
		}
		if (ft_strncmp(line + i, "NO ", 3) == 0
			|| ft_strncmp(line + i, "SO ", 3) == 0
			|| ft_strncmp(line + i, "WE ", 3) == 0
			|| ft_strncmp(line + i, "EA ", 3) == 0
			|| ft_strncmp(line + i, "F ", 2) == 0
			|| ft_strncmp(line + i, "C ", 2) == 0)
			return (1);
	}
	return (0);
}

int	is_map_line(char *line)
{
    return (!is_empty_line(line) && !is_config_line(line));
}
