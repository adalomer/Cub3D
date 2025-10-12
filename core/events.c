/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:51:50 by omadali           #+#    #+#             */
/*   Updated: 2025/10/12 04:39:35 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include "../libs/minilibx-linux/mlx.h"

int	close_window(t_info *info)
{
	mlx_destroy_window(info->mlx, info->win);
	safe_exit(0);
	return (0);
}

int	key_press(int keycode, t_info *info)
{
	if (keycode == ESC_KEY)
		close_window(info);
	else if (keycode == W_KEY)
		info->keys.w = 1;
	else if (keycode == S_KEY)
		info->keys.s = 1;
	else if (keycode == A_KEY)
		info->keys.a = 1;
	else if (keycode == D_KEY)
		info->keys.d = 1;
	else if (keycode == LEFT_ARROW)
		info->keys.left = 1;
	else if (keycode == RIGHT_ARROW)
		info->keys.right = 1;
	return (0);
}

int	key_release(int keycode, t_info *info)
{
	if (keycode == W_KEY)
		info->keys.w = 0;
	else if (keycode == S_KEY)
		info->keys.s = 0;
	else if (keycode == A_KEY)
		info->keys.a = 0;
	else if (keycode == D_KEY)
		info->keys.d = 0;
	else if (keycode == LEFT_ARROW)
		info->keys.left = 0;
	else if (keycode == RIGHT_ARROW)
		info->keys.right = 0;
	return (0);
}

int	game_loop(t_info *info)
{
	if (info->keys.w)
		move_forward(info);
	if (info->keys.s)
		move_backward(info);
	if (info->keys.a)
		move_left(info);
	if (info->keys.d)
		move_right(info);
	if (info->keys.left)
		rotate_left(info);
	if (info->keys.right)
		rotate_right(info);
	
	draw_frame(info);
	return (0);
}
