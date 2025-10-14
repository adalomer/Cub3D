/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:12:48 by omadali           #+#    #+#             */
/*   Updated: 2025/10/14 16:11:06 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include "../headers/libft.h"
#include <math.h>

static void	set_player_info(t_info *info, int x, int y, char dir)
{
	info->player_dir = dir;
	info->player_x = (double)x + 0.5;
	info->player_y = (double)y + 0.5;
	if (dir == 'N')
		info->player_angle = -M_PI / 2;
	else if (dir == 'S')
		info->player_angle = M_PI / 2;
	else if (dir == 'W')
		info->player_angle = M_PI;
	else if (dir == 'E')
		info->player_angle = 0;
}

static int	check_character(t_info *info, int x, int y, int *player_count)
{
	if (ft_strchr("NSEW", info->map[y][x]))
	{
		set_player_info(info, x, y, info->map[y][x]);
		(*player_count)++;
	}
	else if (!ft_strchr("01 ", info->map[y][x]))
		return (0);
	return (1);
}

static int	check_characters_and_player(t_info *info)
{
	int	x;
	int	y;
	int	player_count;

	if (!info || !info->map)
		return (ft_putstr_fd("Error: NULL map pointer\n", 2), 0);
	player_count = 0;
	y = -1;
	while (info->map[++y])
	{
		if (!info->map[y])
			return (ft_putstr_fd("Error: NULL map line\n", 2), 0);
		x = -1;
		while (info->map[y][++x])
			if (!check_character(info, x, y, &player_count))
				return (ft_putstr_fd("Error: Invalid map character\n", 2), 0);
	}
	if (player_count != 1)
		return (ft_putstr_fd("Error: Invalid player count\n", 2), 0);
	return (1);
}

int	validate_map(t_info *info)
{
	if (!info)
	{
		ft_putstr_fd("Error: NULL info pointer\n", 2);
		return (0);
	}
	if (!info->map)
	{
		ft_putstr_fd("Error: NULL map\n", 2);
		return (0);
	}
	if (info->map_height < 3)
	{
		ft_putstr_fd("Error: Map too small (min 3 lines)\n", 2);
		return (0);
	}
	if (!check_characters_and_player(info))
		return (0);
	return (1);
}
