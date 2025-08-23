/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:29:58 by omadali           #+#    #+#             */
/*   Updated: 2025/08/23 23:35:33 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

t_info	*init_info(void)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info->no_texture = NULL;
	info->so_texture = NULL;
	info->we_texture = NULL;
	info->ea_texture = NULL;
	info->floor_color = -1;
	info->ceiling_color = -1;
	info->identifiers_found = 0;
	info->map = NULL;
	info->map_width = 0;
	info->map_height = 0;
	info->player_x = 0;
	info->player_y = 0;
	info->player_dir = '\0';
	info->mlx = NULL;
	info->win = NULL;
	return (info);
}

