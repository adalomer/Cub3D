/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_dda.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 05:00:00 by omadali           #+#    #+#             */
/*   Updated: 2025/10/17 19:00:48 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	calculate_wall_bounds(double distance, int *wall_height,
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

void	init_dda_step_x(t_dda *dda, t_info *info)
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
}

void	init_dda_step_y(t_dda *dda, t_info *info)
{
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

void	init_dda_vars(t_dda *dda, t_info *info, double angle)
{
	dda->ray_dir_x = cos(angle);
	dda->ray_dir_y = sin(angle);
	dda->map_x = (int)info->player_x;
	dda->map_y = (int)info->player_y;
	if (dda->ray_dir_x == 0)
		dda->delta_dist_x = 1e30;
	else
		dda->delta_dist_x = fabs(1 / dda->ray_dir_x);
	if (dda->ray_dir_y == 0)
		dda->delta_dist_y = 1e30;
	else
		dda->delta_dist_y = fabs(1 / dda->ray_dir_y);
	init_dda_step_x(dda, info);
	init_dda_step_y(dda, info);
}

int	perform_dda(t_dda *dda, t_info *info)
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
		if (dda->map_x < 0 || dda->map_y < 0
			|| dda->map_y >= info->map_height
			|| dda->map_x >= (int)ft_strlen(info->map[dda->map_y]))
			break ;
		if (info->map[dda->map_y][dda->map_x] == '1')
			hit = 1;
	}
	return (dda->side);
}

int	is_out_of_bounds(t_info *info, double x, double y)
{
	if (x < 0 || y < 0 || (int)y >= info->map_height
		|| (int)x >= (int)ft_strlen(info->map[(int)y]))
		return (1);
	return (0);
}
