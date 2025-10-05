/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:30:06 by omadali           #+#    #+#             */
/*   Updated: 2025/10/05 14:33:39 by omadali          ###   ########.fr       */
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
	t_ray_result ray_result;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		ray_angle = info->player_angle - FOV / 2 + (double)x / SCREEN_WIDTH * FOV;
		ray_result = cast_single_ray_detailed(info, ray_angle);
		
		// Fisheye correction
		distance = ray_result.distance * cos(ray_angle - info->player_angle);
		
		// Prevent division by zero and unrealistic distances
		if (distance < 0.1)
			distance = 0.1;
		if (distance > 50.0)
			distance = 50.0;
		
		// Calculate wall height with reasonable limits
		wall_height = (int)(SCREEN_HEIGHT / distance);
		if (wall_height > SCREEN_HEIGHT * 2)
			wall_height = SCREEN_HEIGHT * 2;
		if (wall_height < 1)
			wall_height = 1;
		wall_start = (SCREEN_HEIGHT - wall_height) / 2;
		wall_end = wall_start + wall_height;
		
		draw_textured_line(info, x, wall_start, wall_end, &ray_result);
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

t_ray_result	cast_single_ray_detailed(t_info *info, double angle)
{
	t_ray_result result;
	double	x, y, dx, dy, step_size;
	double	prev_x, prev_y;

	x = info->player_x;
	y = info->player_y;
	step_size = 0.005; // Smaller step for smoother walls
	dx = cos(angle) * step_size;
	dy = sin(angle) * step_size;
	result.distance = 0;
	result.texture = NULL;
	
	while (result.distance < 30)
	{
		prev_x = x;
		prev_y = y;
		x += dx;
		y += dy;
		result.distance += step_size;
		
		if (x < 0 || y < 0 || (int)y >= info->map_height || 
			(int)x >= (int)ft_strlen(info->map[(int)y]))
			break;
			
		if (info->map[(int)y][(int)x] == '1')
		{
			// Determine wall hit side and texture coordinates
			if (fabs(x - prev_x) > fabs(y - prev_y))
			{
				// Hit vertical wall (East/West)
				result.hit_side = 0;
				if (dx > 0)
				{
					result.wall_direction = 2; // East
					result.texture = &info->textures.east;
				}
				else
				{
					result.wall_direction = 3; // West
					result.texture = &info->textures.west;
				}
				result.wall_x = y - floor(y); // Texture Y coordinate
			}
			else
			{
				// Hit horizontal wall (North/South)
				result.hit_side = 1;
				if (dy > 0)
				{
					result.wall_direction = 1; // South
					result.texture = &info->textures.south;
				}
				else
				{
					result.wall_direction = 0; // North
					result.texture = &info->textures.north;
				}
				result.wall_x = x - floor(x); // Texture X coordinate
			}
			
			// Adjust wall_x for proper texture mapping
			if ((result.hit_side == 0 && dx > 0) || (result.hit_side == 1 && dy < 0))
				result.wall_x = 1.0 - result.wall_x;
			
			break;
		}
	}
	
	return (result);
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

