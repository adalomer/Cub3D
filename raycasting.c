/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:30:06 by omadali           #+#    #+#             */
/*   Updated: 2025/10/12 04:39:35 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

static void	calculate_wall_bounds(double distance, int *wall_height,
		int *wall_start, int *wall_end)
{
	if (distance < 0.01)
		distance = 0.01;
	*wall_height = (int)(SCREEN_HEIGHT / distance);
	if (*wall_height > SCREEN_HEIGHT * 10)
		*wall_height = SCREEN_HEIGHT * 10;
	if (*wall_height < 1)
		*wall_height = 1;
	*wall_start = (SCREEN_HEIGHT - *wall_height) / 2;
	*wall_end = *wall_start + *wall_height;
}

static void	draw_ray(t_info *info, int x, t_ray_result *ray_result,
		double ray_angle)
{
	int				wall_height;
	int				wall_start;
	int				wall_end;
	t_draw_params	params;
	double			distance;

	distance = ray_result->distance * cos(ray_angle - info->player_angle);
	calculate_wall_bounds(distance, &wall_height, &wall_start, &wall_end);
	params.info = info;
	params.x = x;
	params.start = wall_start;
	params.end = wall_end;
	params.ray = ray_result;
	draw_textured_line(params);
}

void	cast_rays(t_info *info)
{
	int				x;
	double			ray_angle;
	t_ray_result	ray_result;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		ray_angle = info->player_angle - FOV / 2
			+ (double)x / SCREEN_WIDTH * FOV;
		ray_result = cast_single_ray_detailed(info, ray_angle);
		draw_ray(info, x, &ray_result, ray_angle);
	}
}

double	cast_single_ray(t_info *info, double angle)
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	distance;

	x = info->player_x;
	y = info->player_y;
	dx = cos(angle) * 0.05;
	dy = sin(angle) * 0.05;
	distance = 0;
	while (distance < 20)
	{
		x += dx;
		y += dy;
		distance += 0.05;
		if (is_out_of_bounds(info, x, y))
			break;
		if (info->map[(int)y][(int)x] == '1')
			break;
	}
	return (distance);
}

static void	init_dda_step(t_dda *dda, t_info *info)
{
	if (dda->ray_dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (info->player_x - dda->map_x) * dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (dda->map_x + 1.0 - info->player_x)
			* dda->delta_dist_x;
	}
	if (dda->ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (info->player_y - dda->map_y) * dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (dda->map_y + 1.0 - info->player_y)
			* dda->delta_dist_y;
	}
}

static void	init_dda_vars(t_dda *dda, t_info *info, double angle)
{
	dda->ray_dir_x = cos(angle);
	dda->ray_dir_y = sin(angle);
	dda->map_x = (int)info->player_x;
	dda->map_y = (int)info->player_y;
	dda->delta_dist_x = (dda->ray_dir_x == 0) ? 1e30 : fabs(1 / dda->ray_dir_x);
	dda->delta_dist_y = (dda->ray_dir_y == 0) ? 1e30 : fabs(1 / dda->ray_dir_y);
	init_dda_step(dda, info);
}

static int	perform_dda(t_dda *dda, t_info *info)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			dda->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			dda->map_y += dda->step_y;
			dda->side = 1;
		}
		if (dda->map_x < 0 || dda->map_y < 0 || dda->map_y >= info->map_height || 
			dda->map_x >= (int)ft_strlen(info->map[dda->map_y]))
			break;
		if (info->map[dda->map_y][dda->map_x] == '1')
			hit = 1;
	}
	return (dda->side);
}

static void	set_texture_direction(t_ray_result *result, int side,
		int step_x, int step_y, t_info *info)
{
	if (side == 0)
	{
		if (step_x > 0)
		{
			result->wall_direction = 2;
			result->texture = &info->textures.east;
		}
		else
		{
			result->wall_direction = 3;
			result->texture = &info->textures.west;
		}
	}
	else
	{
		if (step_y > 0)
		{
			result->wall_direction = 1;
			result->texture = &info->textures.south;
		}
		else
		{
			result->wall_direction = 0;
			result->texture = &info->textures.north;
		}
	}
}

t_ray_result	cast_single_ray_detailed(t_info *info, double angle)
{
	t_ray_result	result;
	t_dda			dda;
	double			wall_x;

	init_dda_vars(&dda, info, angle);
	dda.side = perform_dda(&dda, info);
	if (dda.side == 0)
		result.distance = (dda.map_x - info->player_x
				+ (1 - dda.step_x) / 2) / dda.ray_dir_x;
	else
		result.distance = (dda.map_y - info->player_y
				+ (1 - dda.step_y) / 2) / dda.ray_dir_y;
	if (dda.side == 0)
		wall_x = info->player_y + result.distance * dda.ray_dir_y;
	else
		wall_x = info->player_x + result.distance * dda.ray_dir_x;
	wall_x -= floor(wall_x);
	result.wall_x = wall_x;
	result.hit_side = dda.side;
	set_texture_direction(&result, dda.side, dda.step_x, dda.step_y, info);
	return (result);
}
