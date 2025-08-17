/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_loops.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:21:21 by yitani            #+#    #+#             */
/*   Updated: 2025/08/17 17:19:26 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	validate_map_content(t_cub3d *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map.grid[i])
	{
		j = 0;
		while (cub->map.grid[i][j])
		{
			if (!is_valid_char(cub->map.grid[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	valid_player_count(t_cub3d *cub)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (cub->map.grid[i])
	{
		j = 0;
		while (cub->map.grid[i][j])
		{
			if (cub->map.grid[i][j] == 'N' || cub->map.grid[i][j] == 'S'
				|| cub->map.grid[i][j] == 'E' || cub->map.grid[i][j] == 'W')
				player_count += 1;
			j++;
		}
		i++;
	}
	return (player_count == 1);
}
