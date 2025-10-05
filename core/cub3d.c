/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 15:00:00 by omadali           #+#    #+#             */
/*   Updated: 2025/10/05 14:33:47 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include "../libs/minilibx-linux/mlx.h"
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int	is_valid_file(const char *filename)
{
	const char	*ext;

	ext = ft_strrchr(filename, '.');
	if (!ext || ft_strncmp(ext, ".cub", 5) != 0)
		return (0);
	return (1);
}

int	open_fd(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_putstr_fd("Error: Could not open file.\n", 2);
	return (fd);
}

void	close_fd(int fd)
{
	if (fd >= 0)
		close(fd);
}

void	safe_exit(int code)
{
	exit(code);
}

static t_texture_image	load_texture_image(t_info *info, char *path)
{
	t_texture_image	img;
	char			abs_path[1024];

	// Initialize to safe values
	img.ptr = NULL;
	img.data_addr = NULL;
	img.width = 64;
	img.height = 64;

	if (!path || !info->mlx)
	{
		printf("Warning: NULL path or MLX\n");
		return (img);
	}

	printf("Attempting to load: %s\n", path);

	// Try relative path first
	img.ptr = mlx_xpm_file_to_image(info->mlx, path, &img.width, &img.height);
	
	// If failed, try absolute path
	if (!img.ptr)
	{
		snprintf(abs_path, sizeof(abs_path), "/home/omadali/Masaüstü/cub3d/%s", path);
		printf("Trying absolute: %s\n", abs_path);
		img.ptr = mlx_xpm_file_to_image(info->mlx, abs_path, &img.width, &img.height);
	}
	
	if (!img.ptr)
	{
		printf("Warning: Failed to load texture: %s\n", path);
		return (img);
	}

	// Get image data address
	img.data_addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, 
		&img.size_line, &img.endian);
	if (!img.data_addr)
	{
		printf("Warning: Failed to get texture data: %s\n", path);
		mlx_destroy_image(info->mlx, img.ptr);
		img.ptr = NULL;
		return (img);
	}

	printf("Texture loaded: %s (%dx%d)\n", path, img.width, img.height);
	return (img);
}

static t_texture_image	create_simple_texture(t_info *info, int color)
{
	t_texture_image	img;
	int				*pixel_data;
	int				i;

	// Create a simple 64x64 colored texture
	img.ptr = mlx_new_image(info->mlx, 64, 64);
	if (!img.ptr)
	{
		printf("Failed to create simple texture\n");
		img = (t_texture_image){0};
		return (img);
	}

	img.width = 64;
	img.height = 64;
	img.data_addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, 
		&img.size_line, &img.endian);

	if (!img.data_addr)
	{
		mlx_destroy_image(info->mlx, img.ptr);
		img = (t_texture_image){0};
		return (img);
	}

	// Fill with solid color
	pixel_data = (int*)img.data_addr;
	i = 0;
	while (i < 64 * 64)
	{
		pixel_data[i] = color;
		i++;
	}

	printf("Created simple texture with color 0x%X\n", color);
	return (img);
}

static int	load_textures(t_info *info)
{
	printf("Trying to load XPM textures with manual fallback...\n");
	
	// Try to load XPM, fallback to manual creation
	if (info->no)
	{
		info->textures.north = load_texture_image(info, info->no);
		if (!info->textures.north.ptr)
			info->textures.north = create_simple_texture(info, 0x96CEB4); // Green
	}
	else
		info->textures.north = create_simple_texture(info, 0x96CEB4);
		
	if (info->so)
	{
		info->textures.south = load_texture_image(info, info->so);
		if (!info->textures.south.ptr)
			info->textures.south = create_simple_texture(info, 0x45B7D1); // Blue
	}
	else
		info->textures.south = create_simple_texture(info, 0x45B7D1);
		
	if (info->ea)
	{
		info->textures.east = load_texture_image(info, info->ea);
		if (!info->textures.east.ptr)
			info->textures.east = create_simple_texture(info, 0xFF6B6B); // Red
	}
	else
		info->textures.east = create_simple_texture(info, 0xFF6B6B);
		
	if (info->we)
	{
		info->textures.west = load_texture_image(info, info->we);
		if (!info->textures.west.ptr)
			info->textures.west = create_simple_texture(info, 0x4ECDC4); // Cyan
	}
	else
		info->textures.west = create_simple_texture(info, 0x4ECDC4);
	
	return (1);
}

void	cub_main(t_info *info)
{
	info->mlx = mlx_init();
	if (!info->mlx)
	{
		ft_putstr_fd("Error: mlx_init() failed.\n", 2);
		safe_exit(1);
	}
	
	info->win = mlx_new_window(info->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	if (!info->win)
	{
		ft_putstr_fd("Error: mlx_new_window() failed.\n", 2);
		safe_exit(1);
	}
	
	if (!load_textures(info))
		safe_exit(1);
	
	mlx_hook(info->win, 17, 0, close_window, info);
	mlx_key_hook(info->win, key_press, info);
	mlx_loop_hook(info->mlx, game_loop, info);
	mlx_loop(info->mlx);
}
