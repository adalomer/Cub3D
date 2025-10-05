/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:12:48 by omadali           #+#    #+#             */
/*   Updated: 2025/08/23 23:33:54 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include "../headers/libft.h"
#include <math.h>

static int	check_characters_and_player(t_info *info)
{
	int	x;
	int	y;
	int	player_count;

	player_count = 0;
	y = 0;
	while (info->map[y])
	{
		x = 0;
		while (info->map[y][x])
		{		if (ft_strchr("NSEW", info->map[y][x]))
		{
			info->player_dir = info->map[y][x];
			info->player_x = (double)x + 0.5;
			info->player_y = (double)y + 0.5;
			if (info->map[y][x] == 'N')
				info->player_angle = -M_PI / 2;
			else if (info->map[y][x] == 'S')
				info->player_angle = M_PI / 2;
			else if (info->map[y][x] == 'W')
				info->player_angle = M_PI;
			else if (info->map[y][x] == 'E')
				info->player_angle = 0;
			player_count++;
		}
			else if (!ft_strchr("01 ", info->map[y][x]))
				return (ft_putstr_fd("Error: Invalid map character\n", 2), 0);
			x++;
		}
		y++;
	}
	if (player_count != 1)
		return (ft_putstr_fd("Error: Invalid player count\n", 2), 0);
	return (1);
}

int	validate_map(t_info *info)
{
	if (!check_characters_and_player(info))
		return (0);
	return (1);
}