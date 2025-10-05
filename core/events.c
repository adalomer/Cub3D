/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 15:00:00 by omadali           #+#    #+#             */
/*   Updated: 2025/10/05 15:00:00 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include "../libs/minilibx-linux/mlx.h"

#define ESC_KEY 65307
#define W_KEY 119
#define S_KEY 115
#define A_KEY 97
#define D_KEY 100
#define LEFT_ARROW 65361
#define RIGHT_ARROW 65363

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
		move_forward(info);
	else if (keycode == S_KEY)
		move_backward(info);
	else if (keycode == A_KEY)
		move_left(info);
	else if (keycode == D_KEY)
		move_right(info);
	else if (keycode == LEFT_ARROW)
		rotate_left(info);
	else if (keycode == RIGHT_ARROW)
		rotate_right(info);
	return (0);
}

int	game_loop(t_info *info)
{
	draw_frame(info);
	return (0);
}
