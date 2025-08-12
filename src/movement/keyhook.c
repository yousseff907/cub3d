/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:54:55 by odana             #+#    #+#             */
/*   Updated: 2025/08/12 16:55:08 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	key_hook(int keycode, t_cub3d *cub)
{
	if (keycode == ESC_KEY)
		exit(0);
	if (keycode == W_KEY)
		move_forward(cub);
	if (keycode == S_KEY)
		move_backward(cub);
	if (keycode == A_KEY)
		move_left(cub);
	if (keycode == D_KEY)
		move_right(cub);
	if (keycode == LEFT_KEY)
		rotate_left(cub);
	if (keycode == RIGHT_KEY)
		rotate_right(cub);
	render_frame(cub);
	return (0);
}
