/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_loops.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:21:21 by yitani            #+#    #+#             */
/*   Updated: 2025/08/20 02:37:17 by odana            ###   ########.fr       */
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

int	find_player_position(t_cub3d *cub, int *player_x, int *player_y)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->map.height)
	{
		j = 0;
		while (cub->map.grid[i][j])
		{
			if (cub->map.grid[i][j] == 'N' || cub->map.grid[i][j] == 'S' ||
				cub->map.grid[i][j] == 'E' || cub->map.grid[i][j] == 'W')
			{
				*player_x = j;
				*player_y = i;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

t_position	*find_all_empty_positions(t_cub3d *cub)
{
	t_position	*positions;
	int			i;
	int			j;

	positions = NULL;
	i = 0;
	while (i < cub->map.height)
	{
		j = 0;
		while (cub->map.grid[i][j])
		{
			if (cub->map.grid[i][j] == '0' || cub->map.grid[i][j] == 'N'
				|| cub->map.grid[i][j] == 'S' || cub->map.grid[i][j] == 'E'
				|| cub->map.grid[i][j] == 'W' || cub->map.grid[i][j] == 'D')
				add_position_to_list(&positions, j, i);
			j++;
		}
		i++;
	}
	return (positions);
}
