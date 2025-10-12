/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 04:00:00 by omadali           #+#    #+#             */
/*   Updated: 2025/10/12 04:39:35 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

int	is_out_of_bounds(t_info *info, double x, double y)
{
	if (x < 0 || y < 0 || (int)y >= info->map_height
		|| (int)x >= (int)ft_strlen(info->map[(int)y]))
		return (1);
	return (0);
}

static int	get_hit_color(double dx, double dy, double x, double prev_x,
		double y, double prev_y)
{
	if (fabs(x - prev_x) > fabs(y - prev_y))
	{
		if (dx > 0)
			return (0xFF6B6B);
		else
			return (0x4ECDC4);
	}
	else
	{
		if (dy > 0)
			return (0x45B7D1);
		else
			return (0x96CEB4);
	}
}

int	get_wall_color(t_info *info, double angle)
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	prev_x;
	double	prev_y;

	x = info->player_x;
	y = info->player_y;
	dx = cos(angle) * 0.05;
	dy = sin(angle) * 0.05;
	while (1)
	{
		prev_x = x;
		prev_y = y;
		x += dx;
		y += dy;
		if (is_out_of_bounds(info, x, y))
			break;
		if (info->map[(int)y][(int)x] == '1')
			return (get_hit_color(dx, dy, x, prev_x, y, prev_y));
	}
	return (0x808080);
}
