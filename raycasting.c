/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:30:06 by omadali           #+#    #+#             */
/*   Updated: 2025/10/11 19:39:02 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"
#include <math.h>

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
		
		distance = ray_result.distance * cos(ray_angle - info->player_angle);
		
		if (distance < 0.01)
			distance = 0.01;
		
		wall_height = (int)(SCREEN_HEIGHT / distance);
		
		if (wall_height > SCREEN_HEIGHT * 10)
			wall_height = SCREEN_HEIGHT * 10;
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
	double ray_dir_x, ray_dir_y;
	int map_x, map_y;
	double side_dist_x, side_dist_y;
	double delta_dist_x, delta_dist_y;
	int step_x, step_y;
	int hit;
	int side;
	
	ray_dir_x = cos(angle);
	ray_dir_y = sin(angle);
	
	map_x = (int)info->player_x;
	map_y = (int)info->player_y;
	
	delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
	delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);
	
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (info->player_x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - info->player_x) * delta_dist_x;
	}
	
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (info->player_y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - info->player_y) * delta_dist_y;
	}
	
	hit = 0;
	while (hit == 0)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		
		if (map_x < 0 || map_y < 0 || map_y >= info->map_height || 
			map_x >= (int)ft_strlen(info->map[map_y]))
			break;
		if (info->map[map_y][map_x] == '1')
			hit = 1;
	}
	
	if (side == 0)
		result.distance = (map_x - info->player_x + (1 - step_x) / 2) / ray_dir_x;
	else
		result.distance = (map_y - info->player_y + (1 - step_y) / 2) / ray_dir_y;
	
	double wall_x;
	if (side == 0)
		wall_x = info->player_y + result.distance * ray_dir_y;
	else
		wall_x = info->player_x + result.distance * ray_dir_x;
	wall_x -= floor(wall_x);
	
	result.wall_x = wall_x;
	result.hit_side = side;
	
	if (side == 0)
	{
		if (step_x > 0)
		{
			result.wall_direction = 2;
			result.texture = &info->textures.east;
		}
		else
		{
			result.wall_direction = 3;
			result.texture = &info->textures.west;
		}
	}
	else
	{
		if (step_y > 0)
		{
			result.wall_direction = 1;
			result.texture = &info->textures.south;
		}
		else
		{
			result.wall_direction = 0;
			result.texture = &info->textures.north;
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
	}
	return (0x808080);
}

