/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:30:06 by omadali           #+#    #+#             */
/*   Updated: 2025/10/05 15:00:00 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"
#include <math.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FOV (M_PI / 3)

void	cast_rays(t_info *info)
{
	int		x;
	double	ray_angle;
	double	distance;
	int		wall_height;
	int		wall_start;
	int		wall_end;
	int		wall_color;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		ray_angle = info->player_angle - FOV / 2 + (double)x / SCREEN_WIDTH * FOV;
		distance = cast_single_ray(info, ray_angle);
		distance = distance * cos(ray_angle - info->player_angle);
		wall_height = (int)(SCREEN_HEIGHT / distance);
		wall_start = (SCREEN_HEIGHT - wall_height) / 2;
		wall_end = wall_start + wall_height;
		wall_color = get_wall_color(info, ray_angle);
		draw_vertical_line(info, x, wall_start, wall_end, wall_color);
		x++;
	}
}

double	cast_single_ray(t_info *info, double angle)
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	distance;
	double	step_size;

	x = info->player_x;
	y = info->player_y;
	step_size = 0.05;
	dx = cos(angle) * step_size;
	dy = sin(angle) * step_size;
	distance = 0;
	while (distance < 20)
	{
		x += dx;
		y += dy;
		distance += step_size;
		if (x < 0 || y < 0 || (int)y >= info->map_height || 
			(int)x >= (int)ft_strlen(info->map[(int)y]))
			break;
		if (info->map[(int)y][(int)x] == '1')
			break;
	}
	return (distance);
}

int	get_wall_color(t_info *info, double angle)
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	step_size;
	double	prev_x;
	double	prev_y;

	x = info->player_x;
	y = info->player_y;
	step_size = 0.05;
	dx = cos(angle) * step_size;
	dy = sin(angle) * step_size;
	
	while (1)
	{
		prev_x = x;
		prev_y = y;
		x += dx;
		y += dy;
		if (x < 0 || y < 0 || (int)y >= info->map_height || 
			(int)x >= (int)ft_strlen(info->map[(int)y]))
			break;
		if (info->map[(int)y][(int)x] == '1')
		{
			// Determine wall direction
			if (fabs(x - prev_x) > fabs(y - prev_y))
			{
				// Hit vertical wall
				if (dx > 0)
					return (0xFF6B6B); // East wall - red
				else
					return (0x4ECDC4); // West wall - cyan
			}
			else
			{
				// Hit horizontal wall  
				if (dy > 0)
					return (0x45B7D1); // South wall - blue
				else
					return (0x96CEB4); // North wall - green
			}
		}
	}
	return (0x808080); // Default gray
}

