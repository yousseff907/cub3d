/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:54:55 by odana             #+#    #+#             */
/*   Updated: 2025/08/20 09:30:48 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int key_press(int keycode, t_cub3d *cub)
{
    if (keycode == ESC_KEY)
        exit(0);
    if (keycode == W_KEY)
        cub->keys.w_pressed = 1;
    if (keycode == S_KEY)
        cub->keys.s_pressed = 1;
    if (keycode == A_KEY)
        cub->keys.a_pressed = 1;
    if (keycode == D_KEY)
        cub->keys.d_pressed = 1;
    return (0);
}

int key_release(int keycode, t_cub3d *cub)
{
    if (keycode == W_KEY)
        cub->keys.w_pressed = 0;
    if (keycode == S_KEY)
        cub->keys.s_pressed = 0;
    if (keycode == A_KEY)
        cub->keys.a_pressed = 0;
    if (keycode == D_KEY)
        cub->keys.d_pressed = 0;
    return (0);
}

int game_loop(t_cub3d *cub)
{
    update_doors(cub);
    update_sprites(cub);
    if (cub->keys.w_pressed)
        move_forward(cub);
    if (cub->keys.s_pressed)
        move_backward(cub);
    if (cub->keys.a_pressed)
        move_left(cub);
    if (cub->keys.d_pressed)
        move_right(cub);
    render_frame(cub);
    return (0);
}

int close_window(t_cub3d *cub)
{
    cleanup_cub3d(cub);
    exit(1);
    return (0);
}