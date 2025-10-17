/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 04:00:00 by omadali           #+#    #+#             */
/*   Updated: 2025/10/17 19:00:51 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

typedef struct s_hit_data
{
	double	dx;
	double	dy;
	double	x;
	double	prev_x;
	double	y;
	double	prev_y;
}	t_hit_data;

void	draw_ray(t_info *info, int x, t_ray_result *ray_result,
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

static int	get_hit_color(t_hit_data hit)
{
	if (fabs(hit.x - hit.prev_x) > fabs(hit.y - hit.prev_y))
	{
		if (hit.dx > 0)
			return (0xFF6B6B);
		else
			return (0x4ECDC4);
	}
	else
	{
		if (hit.dy > 0)
			return (0x45B7D1);
		else
			return (0x96CEB4);
	}
}

int	get_wall_color(t_info *info, double angle)
{
	t_hit_data	hit;
	double		x;
	double		y;

	x = info->player_x;
	y = info->player_y;
	hit.dx = cos(angle) * 0.05;
	hit.dy = sin(angle) * 0.05;
	while (1)
	{
		hit.prev_x = x;
		hit.prev_y = y;
		x += hit.dx;
		y += hit.dy;
		if (is_out_of_bounds(info, x, y))
			break ;
		if (info->map[(int)y][(int)x] == '1')
		{
			hit.x = x;
			hit.y = y;
			return (get_hit_color(hit));
		}
	}
	return (0x808080);
}

static void	set_horizontal_texture(t_ray_result *result,
		t_dda *dda, t_info *info)
{
	if (dda->step_x > 0)
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

static void	set_vertical_texture(t_ray_result *result,
		t_dda *dda, t_info *info)
{
	if (dda->step_y > 0)
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

void	set_texture_direction(t_ray_result *result, t_dda *dda, t_info *info)
{
	if (dda->side == 0)
		set_horizontal_texture(result, dda, info);
	else
		set_vertical_texture(result, dda, info);
}
