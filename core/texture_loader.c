/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:51:56 by omadali           #+#    #+#             */
/*   Updated: 2025/10/12 04:39:35 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include "../libs/minilibx-linux/mlx.h"
#include <stdio.h>

static void	try_absolute_path(t_info *info, char *path, t_texture_image *img)
{
	char	abs_path[1024];
	char	cwd[1024];

	snprintf(abs_path, sizeof(abs_path), "%s", path);
	if (abs_path[0] == '.')
	{
		getcwd(cwd, sizeof(cwd));
		snprintf(abs_path, sizeof(abs_path), "%s/%s", cwd, path + 2);
	}
	printf("Trying absolute: %s\n", abs_path);
	img->ptr = mlx_xpm_file_to_image(info->mlx, abs_path,
			&img->width, &img->height);
}

t_texture_image	load_texture_image(t_info *info, char *path)
{
	t_texture_image	img;

	img = (t_texture_image){NULL, NULL, 0, 0, 0, 64, 64};
	if (!path || !info->mlx)
		return (printf("Warning: NULL path or MLX\n"), img);
	printf("Attempting to load: %s\n", path);
	img.ptr = mlx_xpm_file_to_image(info->mlx, path, &img.width, &img.height);
	if (!img.ptr)
		try_absolute_path(info, path, &img);
	if (!img.ptr)
		return (printf("Warning: Failed to load texture: %s\n", path),
			printf("MLX Error - file may not exist or invalid XPM format\n"),
			img);
	img.data_addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel,
			&img.size_line, &img.endian);
	if (!img.data_addr)
	{
		printf("Warning: Failed to get texture data: %s\n", path);
		return (mlx_destroy_image(info->mlx, img.ptr),
			img.ptr = NULL, img);
	}
	return (printf("Texture loaded: %s (%dx%d)\n", path,
			img.width, img.height), img);
}

static void	fill_texture_pixels(int *pixel_data, int color)
{
	int	i;

	i = 0;
	while (i < 64 * 64)
	{
		pixel_data[i] = color;
		i++;
	}
}

t_texture_image	create_simple_texture(t_info *info, int color)
{
	t_texture_image	img;
	int				*pixel_data;

	img.ptr = mlx_new_image(info->mlx, 64, 64);
	if (!img.ptr)
		return (printf("Failed to create simple texture\n"),
			(t_texture_image){0});
	img.width = 64;
	img.height = 64;
	img.data_addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel,
			&img.size_line, &img.endian);
	if (!img.data_addr)
	{
		mlx_destroy_image(info->mlx, img.ptr);
		return ((t_texture_image){0});
	}
	pixel_data = (int *)img.data_addr;
	fill_texture_pixels(pixel_data, color);
	printf("Created simple texture with color 0x%X\n", color);
	return (img);
}

static void	load_single_texture(t_info *info, char *path,
		t_texture_image *tex, int fallback_color)
{
	if (path)
	{
		*tex = load_texture_image(info, path);
		if (!tex->ptr)
			*tex = create_simple_texture(info, fallback_color);
	}
	else
		*tex = create_simple_texture(info, fallback_color);
}

int	load_textures(t_info *info)
{
	printf("Trying to load XPM textures with manual fallback...\n");
	load_single_texture(info, info->no, &info->textures.north, 0x96CEB4);
	load_single_texture(info, info->so, &info->textures.south, 0x45B7D1);
	load_single_texture(info, info->ea, &info->textures.east, 0xFF6B6B);
	load_single_texture(info, info->we, &info->textures.west, 0x4ECDC4);
	return (1);
}
