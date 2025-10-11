/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:29:58 by omadali           #+#    #+#             */
/*   Updated: 2025/10/11 19:32:58 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

t_info	*init_info(void)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	// Initialize new texture system
	info->textures.north = (t_texture_image){0};
	info->textures.south = (t_texture_image){0};
	info->textures.east = (t_texture_image){0};
	info->textures.west = (t_texture_image){0};
	
	info->texture_north = NULL;
	info->texture_south = NULL;
	info->texture_east = NULL;
	info->texture_west = NULL;
	info->no = NULL;
	info->so = NULL;
	info->ea = NULL;
	info->we = NULL;
	info->no_texture = NULL;
	info->so_texture = NULL;
	info->we_texture = NULL;
	info->ea_texture = NULL;
	info->no_img = NULL;
	info->so_img = NULL;
	info->we_img = NULL;
	info->ea_img = NULL;
	info->tex_width = 64;
	info->tex_height = 64;
	info->floor_color = -1;
	info->ceiling_color = -1;
	info->identifiers_found = 0;
	info->map = NULL;
	info->map_width = 0;
	info->map_height = 0;
	info->player_x = 0;
	info->player_y = 0;
	info->player_dir = '\0';
	info->player_angle = 0;
	info->mlx = NULL;
	info->win = NULL;
	info->img = NULL;
	info->img_data = NULL;
	info->bits_per_pixel = 0;
	info->line_length = 0;
	info->endian = 0;
	
	// Initialize key states
	info->keys.w = 0;
	info->keys.s = 0;
	info->keys.a = 0;
	info->keys.d = 0;
	info->keys.left = 0;
	info->keys.right = 0;
	
	return (info);
}

