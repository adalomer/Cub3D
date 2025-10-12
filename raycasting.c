/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:30:06 by omadali           #+#    #+#             */
/*   Updated: 2025/10/12 05:33:58 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

void	cast_rays(t_info *info)
{
	int				x;
	double			ray_angle;
	t_ray_result	ray_result;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		ray_angle = info->player_angle - (M_PI / FOV_DIVISOR) / 2
			+ (double)x / SCREEN_WIDTH * (M_PI / FOV_DIVISOR);
		ray_result = cast_single_ray_detailed(info, ray_angle);
		draw_ray(info, x, &ray_result, ray_angle);
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
	set_texture_direction(&result, &dda, info);
	return (result);
}
