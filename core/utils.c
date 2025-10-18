/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:51:53 by omadali           #+#    #+#             */
/*   Updated: 2025/10/18 21:31:42 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	move_forward(t_info *info)
{
	double	new_x;
	double	new_y;
	double	dir_x;
	double	dir_y;

	dir_x = cos(info->player_angle);
	dir_y = sin(info->player_angle);
	new_x = info->player_x + dir_x * MOVE_SPEED;
	new_y = info->player_y + dir_y * MOVE_SPEED;
	if (is_valid_position(info, new_x, new_y))
	{
		info->player_x = new_x;
		info->player_y = new_y;
	}
}

void	move_backward(t_info *info)
{
	double	new_x;
	double	new_y;
	double	dir_x;
	double	dir_y;

	dir_x = cos(info->player_angle);
	dir_y = sin(info->player_angle);
	new_x = info->player_x - dir_x * MOVE_SPEED;
	new_y = info->player_y - dir_y * MOVE_SPEED;
	if (is_valid_position(info, new_x, new_y))
	{
		info->player_x = new_x;
		info->player_y = new_y;
	}
}

void	move_left(t_info *info)
{
	double	new_x;
	double	new_y;
	double	dir_x;
	double	dir_y;

	dir_x = cos(info->player_angle - M_PI / 2);
	dir_y = sin(info->player_angle - M_PI / 2);
	new_x = info->player_x + dir_x * MOVE_SPEED;
	new_y = info->player_y + dir_y * MOVE_SPEED;
	if (is_valid_position(info, new_x, new_y))
	{
		info->player_x = new_x;
		info->player_y = new_y;
	}
}

void	move_right(t_info *info)
{
	double	new_x;
	double	new_y;
	double	dir_x;
	double	dir_y;

	dir_x = cos(info->player_angle + M_PI / 2);
	dir_y = sin(info->player_angle + M_PI / 2);
	new_x = info->player_x + dir_x * MOVE_SPEED;
	new_y = info->player_y + dir_y * MOVE_SPEED;
	if (is_valid_position(info, new_x, new_y))
	{
		info->player_x = new_x;
		info->player_y = new_y;
	}
}

/**
 * Optimized pixel drawing function
 */
void	put_pixel(t_info *info, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	
	dst = info->img_data + (y * info->line_length + x * (info->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
