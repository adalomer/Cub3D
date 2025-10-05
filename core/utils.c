/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 15:00:00 by omadali           #+#    #+#             */
/*   Updated: 2025/10/05 15:00:00 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include <math.h>

#define MOVE_SPEED 0.3
#define ROT_SPEED 0.15

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

void	rotate_left(t_info *info)
{
	info->player_angle -= ROT_SPEED;
}

void	rotate_right(t_info *info)
{
	info->player_angle += ROT_SPEED;
}

double	get_player_angle(t_info *info)
{
	return (info->player_angle);
}

int	is_valid_position(t_info *info, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_y < 0 || map_y >= info->map_height || 
		map_x >= (int)ft_strlen(info->map[map_y]))
		return (0);
	if (info->map[map_y][map_x] == '1')
		return (0);
	return (1);
}
