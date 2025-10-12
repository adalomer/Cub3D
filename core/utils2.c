/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 02:00:00 by omadali           #+#    #+#             */
/*   Updated: 2025/10/12 04:39:35 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

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
	int		map_x;
	int		map_y;
	double	margin;

	margin = 0.2;
	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_y < 0 || map_y >= info->map_height
		|| map_x >= (int)ft_strlen(info->map[map_y]))
		return (0);
	if (info->map[map_y][map_x] == '1')
		return (0);
	if (info->map[(int)(y - margin)][(int)(x - margin)] == '1')
		return (0);
	if (info->map[(int)(y - margin)][(int)(x + margin)] == '1')
		return (0);
	if (info->map[(int)(y + margin)][(int)(x - margin)] == '1')
		return (0);
	if (info->map[(int)(y + margin)][(int)(x + margin)] == '1')
		return (0);
	return (1);
}
